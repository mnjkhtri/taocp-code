/*
The RISC-V instrcutions are 32 bit wide:
    31 ... 0 (where 6 ... 0 constitute opcode). Based on this opcode 11 types of instructions:

    1) ALU immediate [9 variants]: 
            reg <- reg OP imm (0010011)

    2) ALU register [10 variants]: 
            reg <- reg OP imm (0110011)

    3) LOAD [5 variants]: 
            reg <- mem[reg+imm] (0000011)

    4) STORE [3 variants]: 
            mem[reg+imm] <- reg (0100011)

    5) JAL [itself]: 
            reg <- PC+4; PC <- PC+imm (1101111)

    6) JALR [itself]: 
            reg <- PC+4; PC <- reg+imm (1100111)

    7) Conditional jump [6 variants]:
            if (reg OP reg) PC <- PC+imm (1100011)

    8) LUI [itself]: 
            reg <- imm << 12 (0110111)

    9) AUIPC [itself]: 
            reg <- PC+(imm<<12) (0010111)

    10) FENCE [itself]:

    11) SYSTEM [itself]: (1110011)

    Based on the number of registers and immediates used the types are:

    1. R-type: (two source registers, one destination register, funct3, funct7)
    2. I-type: (one source register, one immediate, one destination register, funct3)
    3: S-type: (two source register, one immediate, funct3)
    4: U-type: (one immediate, one destination register)

    5: B-type: (same as S-type, handling of immediate differs)
    6: J-type: (same as U-type, handling of immediate differs)
*/

`include "clockworks.v"

module SOC (

    //System intput
    input CLK,
    input RESET,

    //LED output
    output [4:0] LEDS,

    //UART transmissions (not now)
    input RXD,
    output TXD

    ); 

    //Memory from which to fetch the instructions
    reg [31:0] MEM [0:255];

    //Put instructions in memory:
    initial begin

        //addi x1, x1, 10
        MEM[0] = 32'b00000000101000001000000010010011;

        //addi x2, x2, 1       
        MEM[1] = 32'b00000000000100010000000100010011;

        //jal 0, <two up>; use this for jump simulation
        MEM[2] = 32'b11111111110111111111000001101111;

        //bne x1, x2, <twoup>; use this for branch simulation
        //MEM[2] = 32'b11111110001000001001111011100011;

        //ebreak call
        MEM[3] = 32'b000000000001_00000_000_00000_1110011;
    end

    wire clk; //Internal clock (after slowing down)
    wire resetn; //Internal negative reset

    Clockworks #(.SLOW(15)) CW (CLK, RESET, clk, resetn);

    reg [31:0] PC = 0;   //To fetch from memory
    reg [31:0] instr;   //Instruction register
    reg [31:0] RegFile[0:31];   //General purpose registers

    //For benching purpose, initialize them to zero
    `ifdef BENCH
        integer i;
        initial begin
            for (i = 0; i < 32; ++i)
                RegFile[i] = 0;
        end
    `endif

    //First decide out which one of the 11 is the given instruction in the instr register:
    wire isALUimm = (instr[6:0] == 7'b0010011);
    wire isALUreg = (instr[6:0] == 7'b0110011);
    wire isLoad = (instr[6:0] == 7'b0000011);
    wire isStore = (instr[6:0] == 7'b0100011);
    wire isJAL = (instr[6:0] == 7'b1101111);
    wire isJALR = (instr[6:0] == 7'b1100111);
    wire isBranch = (instr[6:0] == 7'b1100011);
    wire isLUI = (instr[6:0] == 7'b0110111);
    wire isAUIPC = (instr[6:0] == 7'b0010111);
    //Leave out system and fence for now

    //Use system to end the simulation during bench
    wire isSYSTEM = (instr[6:0] == 7'b1110011);

    //Extract the register (regardless of whether valid), beauty of RISC-V is that the fields are fixed
    wire [4:0] rdId = instr[11:7];
    wire [4:0] rs1Id = instr[19:15];
    wire [4:0] rs2Id = instr[24:20];

    //Extract the immediate values and sign-extend them (except type-R, five of them got immediates)
    wire [31:0] Iimm = {{21{instr[31]}}, instr[30:20]};
    wire [31:0] Simm = {{21{instr[31]}}, instr[30:25], instr[11:7]};
    wire [31:0] Bimm = {{20{instr[31]}}, instr[7], instr[30:25], instr[11:8], 1'b0};
    wire [31:0] Uimm = {instr[31], instr[30:12], {12{1'b0}}};
    wire [31:0] Jimm = {{12{instr[31]}}, instr[19:12], instr[20], instr[30:21], 1'b0};

    //Function codes:
    wire [2:0] funct3 = instr[14:12];
    wire [6:0] funct7 = instr[31:25];

    //AUTOMATA THAT EXECUTES THE INSTRUCTIONS:
    //State identifiers
    localparam IF = 0;
    localparam ID = 1;
    localparam EX = 2;
    localparam MM = 3;
    localparam WB = 4;

    //Current state
    reg[2:0] state = IF;

    //Temporary source registers:
    reg[31:0] rs1;
    reg[31:0] rs2;

    wire[31:0] WBData;  //Data to be written into registers
    wire isWB;  //Whether the given instruction writes 

    //The execution of instructions is a five state machine:
    /*
    1) Instruction Fetch:
    2) Instruction Decode:
    3) ALU Operation:
    4) Memory access:
    5) Write Back:
    */

    //[1.] Implement ALUimm's and ALUreg's: Calculate aluIn1 op aluIn2 and store in aluOut:

    //Depending on the imm or reg version, the aluIn2 is either second source register or the immediate
    wire [31:0] aluIn1 = rs1;
    wire [31:0] aluIn2 = isALUreg ? rs2 : Iimm;
    reg [31:0] aluOut;
    
    //The aluOut depends upon the type of operation, mostly depends on funct3 (and also on funct4)
    //Decoding of funct3:

    /*
    1. 000: ADD or SUB
        -if bit 5 of funct7 is 1 then SUB
        -if ALUimm then ADD regardless
    2. 001: Left shift
    3. 010: Signed comparison
    4. 011: Unsigned comparison
    5. 100: XOR
    6. 101: Logical right shift or arithmetic right shift
        -if bit 5 of funct7 is 1 then AS else LS
    7. 110: OR
    8. 111: AND
    */
    //The shift amount for each shifts is 5 bits from either rdId or Iimm
    wire [4:0] shamt = isALUreg ? rs2[4:0] : instr[24:20];

    //[2.] Two jump instructions:
    //JAL rd, imm: rd <- PC+4; PC <- PC + Jimm
    //JALR rd, rs1, imm: rd <- PC+4; PC <- rs1 + Iimm

    //[3.] Branch instructions:
    //if (rs1 op rs2) PC <- PC + BImm

    //[4.] LUI and AUIPC:
    //LUI rd, imm; rd <= Uimm
    //AUIPC rd, imm; rd <= PC+Uimm

    //[5.] LOAD and STORE in next module

    reg takeBranch;
    always @(*) begin
        case(funct3)
            3'b000: takeBranch = (rs1 == rs2);
            3'b001: takeBranch = (rs1 != rs2);
            3'b100: takeBranch = ($signed(rs1) < $signed(rs2));
            3'b101: takeBranch = ($signed(rs1) >= $signed(rs2));
            3'b110: takeBranch = (rs1 < rs2);
            3'b111: takeBranch = (rs1 >= rs2);
            default: takeBranch = 1'b0; 
        endcase
    end

    //Make it a combinatorial circuit inside the always block
    always @(*)
    begin
        case(funct3)
            3'b000: aluOut = (funct7[5] & isALUreg) ? (aluIn1 - aluIn2) : (aluIn1 + aluIn2);
	        3'b001: aluOut = aluIn1 << shamt;
	        3'b010: aluOut = ($signed(aluIn1) < $signed(aluIn2));
            3'b011: aluOut = (aluIn1 < aluIn2);
            3'b100: aluOut = (aluIn1 ^ aluIn2);
            3'b101: aluOut = funct7[5]? ($signed(aluIn1) >>> shamt) : ($signed(aluIn1) >> shamt);
            3'b110: aluOut = (aluIn1 | aluIn2); 
            3'b111: aluOut = (aluIn1 & aluIn2);
        endcase
    end

    assign WBData = (isJAL || isJALR) ? (PC+4) :
                    (isLUI) ? Uimm :
                    (isAUIPC) ? (PC + Uimm) :
                    aluOut;

    //Instructions which allow writing to register files
    assign isWB = (isALUreg || isALUimm || isJAL || isJALR || isLUI || isAUIPC);

    //Now possibility for new PC is not just increment
    wire [31:0] nextPC =    isJAL ? PC+Jimm : 
                            isJALR ? PC+Iimm : 
                            (isBranch && takeBranch) ? PC+Bimm :
                            PC+4;

    always @(posedge clk) 
    begin
        if (resetn)
            begin
                PC <= 0;
            end 

        begin
            case (state)
                IF: begin
                    instr <= MEM[PC[31:2]];
                    //Cannot increment PC here cause of continuity
                    state <= ID;
                end

                ID: begin
                    rs1 <= RegFile[rs1Id];
                    rs2 <= RegFile[rs2Id];
                    state <= EX;
                end

                EX: begin
                    PC <= nextPC;
                    state <= MM;
                end

                MM: begin
                    state <= WB;
                end

                WB: begin
                    if (isWB && rdId != 0) RegFile[rdId] <= WBData; //Writing to register 0 has no effect
                    state <= IF;
                end
            endcase
        end
    
        `ifdef BENCH //BENCH can be passed from command line
            if(isSYSTEM) $finish();
        `endif
    end

    //Send some info of the instruction to the LEDs
    assign LEDS = RegFile[2]; 
    assign TXD = 1'b0;  //As always output 1 to UART

    `ifdef BENCH
    //The following is bench portion interpreting the output from the LEDs
    always @(posedge clk)
    begin
        $display(LEDS);
        if (state == ID)
            case (1'b1)
                isALUimm: $display("Current PC=%0d ALUimm", PC);
                isALUreg: $display("Current PC=%0d ALUreg", PC);
                isLoad: $display("Current PC=%0d LOAD", PC);
                isStore: $display("Current PC=%0d STORE", PC);
                isJAL: $display("Current PC=%0d JAL", PC);
                isJALR: $display("Current PC=%0d JALR", PC);
                isBranch: $display("Current PC=%0d BRANCH", PC);
                isLUI: $display("Current PC=%0d LUI", PC);
                isAUIPC: $display("Current PC=%0d AUIPC", PC);
                isSYSTEM: $display("Current PC=%0d SYSTEM", PC);
                default: $display("ILLEGAL");
            endcase
    end
    `endif

endmodule


//The bench module that generates the CLK and RESET signals
module bench();

    //Inputs as registers
    reg CLK;
    reg RESET;
    reg RXD;

    //Output as wires
    wire [4:0] LEDS;
    wire TXD;

    SOC uut (CLK, RESET, LEDS, RXD, TXD);

    //CLK:
    initial CLK = 1'b0;
    always #(1) CLK = ~CLK;

    //RESET:
    //Initially high then after a bit of time,, goes low (ie unreset)
    initial begin RESET = 1'b0; end 

endmodule