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
        MEM[0] = 32'b0000000_00000_00000_000_00000_0110011;
        MEM[5] = 32'b000000000000_00001_010_00010_0000011;
        MEM[6] = 32'b000000_00001_00010_010_00000_0100011;
        MEM[7] = 32'b000000000001_00000_000_00000_1110011;
    end

    wire clk; //Internal clock (after slowing down)
    wire resetn; //Internal negative reset

    Clockworks #(.SLOW(15)) CW (CLK, RESET, clk, resetn);

    reg [31:0] PC = 0;   //To fetch from memory
    reg [31:0] instr;   //Instruction register

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

    //At each clock pulse fetch the instructions (for now dont care the execution)
    always @(posedge clk) 
    begin
        if (resetn)
            begin
                PC <= 0;
                instr <= 32'b0000000_00000_00000_000_00000_0110011; //ALUreg NOP
            end 
        else
            begin
                instr <= MEM[PC];
                PC <= PC + 1;
            end
    
        `ifdef BENCH //BENCH can be passed from command line
            if(isSYSTEM) $finish();
        `endif
    end

    //Send some info of the instruction to the LEDs
    assign LEDS = isSYSTEM ? 31 : {PC[0], isALUreg, isALUimm, isStore, isLoad};
    assign TXD = 1'b0;  //As always output 1 to UART

    `ifdef BENCH
    //The following is bench portion interpreting the output from the LEDs
    always @(posedge clk)
    begin
        case (1'b1)
            isALUimm: $display("PC=%0d ALUimm", PC);
            isALUreg: $display("PC=%0d ALUreg", PC);
            isLoad: $display("PC=%0d LOAD", PC);
            isStore: $display("PC=%0d STORE", PC);
            isJAL: $display("PC=%0d JAL", PC);
            isJALR: $display("PC=%0d JALR", PC);
            isBranch: $display("PC=%0d BRANCH", PC);
            isLUI: $display("PC=%0d LUI", PC);
            isAUIPC: $display("PC=%0d AUIPC", PC);
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
    initial begin RESET = 1'b1; #10 RESET = 1'b0; end 

endmodule