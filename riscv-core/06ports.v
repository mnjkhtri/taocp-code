`include "clockworks.v"

//Memory module: inputs in address and on positive clock edge gives out the output
module Memory (
    input               clk,
    input [31:0]        mem_addr,

    //For reads:
    output reg [31:0]   mem_rdata,
    input               rd_en,

    //For writes:
    input [31:0]        mem_wdata,
    input [3:0]         wmask
);

    //Memory from which to fetch the instructions
    reg [31:0] MEM [0:255];

    //Put instructions in memory:
    initial begin

        //Not using MEM[0] because of clock issues

        //addi x1, x1, 10
        MEM[1] = 32'b00000000101000001000000010010011;

        //addi x2, x2, 1       
        MEM[2] = 32'b00000000000100010000000100010011;

        //jal 0, <two up>; use this for jump simulation
        //MEM[3] = 32'b11111111110111111111000001101111;

        //bne x1, x2, <twoup>; use this for branch simulation
        //MEM[3] = 32'b11111110001000001001111011100011;

        //or some illegal instruction for neither
        //MEM[3] = 32'b00000000000000000000000000000000;

        //SW x1, 400(x0)
        MEM[3] = 32'b00011000000100000010100000100011;

        //LW x1, 400(x0)
        MEM[4] = 32'b00011001000000000010000010000011;

        //ebreak call
        MEM[5] = 32'b000000000001_00000_000_00000_1110011;

        //Memory fillup for loads and stores instructions:
        MEM[100] = {8'h4, 8'h3, 8'h2, 8'h1};

    end

    wire [29:0] word_addr = mem_addr[31:2];
    always @(posedge clk) begin
        if (rd_en)
            mem_rdata <= MEM[word_addr];

        if (wmask[0]) MEM[word_addr][7:0  ] <= mem_wdata[7:0  ];
        if (wmask[1]) MEM[word_addr][15:8 ] <= mem_wdata[15:8 ];
        if (wmask[2]) MEM[word_addr][23:16] <= mem_wdata[23:16];
        if (wmask[3]) MEM[word_addr][31:24] <= mem_wdata[31:24];
    end
endmodule

//Processor module: executes instructions
module Processor (
    input               clk,
    input               resetn,
    output [31:0]       mem_addr,

    //Memory reads:
    input [31:0]        mem_rdata,
    output              rd_en,

    //Memory writes:
    output [31:0]       mem_wdata,
    output [3:0]        wmask
);

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
    localparam ID = 2;
    localparam EX = 3;
    localparam MM = 4;
    localparam WB = 6;

    //New states where waits for data from memory
    localparam IF_WAIT = 1;
    localparam MM_WAIT = 5;

    //Current state
    reg[2:0] state = IF;

    //Temporary source registers:
    reg[31:0] rs1;
    reg[31:0] rs2;

    wire[31:0] WBData;  //Data to be written into registers
    wire isWB;  //Whether the given instruction writes 

    wire [31:0] aluIn1 = rs1;
    wire [31:0] aluIn2 = isALUreg ? rs2 : Iimm;
    reg [31:0] aluOut;
    
    wire [4:0] shamt = isALUreg ? rs2[4:0] : instr[24:20];
    
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
                    (isLoad) ? LOAD_data :
                    aluOut;

    //Instructions which allow writing to register files
    assign isWB = (isALUreg || isALUimm || isJAL || isJALR || isLUI || isAUIPC || isLoad);

    //Now possibility for new PC is not just increment
    wire [31:0] nextPC =    isJAL ? PC+Jimm : 
                            isJALR ? PC+Iimm : 
                            (isBranch && takeBranch) ? PC+Bimm :
                            PC+4;

    //Implement LOADs and STOREs:
    //LOADs: rd <= MEM[rs1+imm]
    //STOREs: MEM[rs1+imm] <= rs2
    //Get the data ready then see which type of load or store it is
    wire [31:0] loadstore_addr = rs1 + (isStore ? Simm : Iimm);    //Byte address to send to get the data

    //Based on alignment of address, get possible bytes, halfwords and words:
    //Alignment means if you want to fetch a word and address is not divisible by 4 then just make it divisible by 4 and return that word
    
    //mem_rdata contains the 32bits based on the same alignment principle ie loadstore_addr[31:2]

    //Depending on loadstore_addr[1] will get lower or higher halfword
    wire [15:0] LOAD_halfword = loadstore_addr[1] ? mem_rdata[31:16] : mem_rdata[15:0];

    //Likewise based on 0th bit, get the lower or higher byte
    wire [7:0] LOAD_byte = loadstore_addr[0] ? LOAD_halfword[15:8] : LOAD_halfword[7:0];

    //See what type of load it is:
    wire mem_byteAccess = (funct3[1:0] == 2'b00);
    wire mem_halfwordAccess = (funct3[1:0] == 2'b01);

    //Sign extension variation funct3[2] signifies whether its a unsigned or signed:
    wire LOAD_sign = !funct3[2] & (mem_byteAccess ? LOAD_byte[7] : LOAD_halfword[15]);

    wire [31:0] LOAD_data = mem_byteAccess ? {{24{LOAD_sign}}, LOAD_byte} :
                            mem_halfwordAccess ? {{16{LOAD_sign}}, LOAD_halfword} :
                            mem_rdata;

    //For store too, same alignment principle:
    //If address is divisible by 4, mem_wdata = whole word
    //If divisible by 2 then, mem_wdata = lowest halfword * 2
    //If neither then, mem_wdata = lowest byte * 4
    //We are nto yet sure which byte, halfword or word store it is??

    assign mem_wdata [7:0  ] = rs2[7:0];
    assign mem_wdata [15:8 ] = loadstore_addr[0] ? rs2[7:0] : rs2[15:8 ]; 
    assign mem_wdata [23:16] = loadstore_addr[1] ? rs2[7:0] : rs2[23:16];
    assign mem_wdata [31:24] = loadstore_addr[0] ? rs2[7:0] : loadstore_addr[1] ? rs2[15:8] : rs2[31:24];

    wire [3:0] STORE_wmask = mem_byteAccess ? (loadstore_addr[1] ? 
                                                (loadstore_addr[0] ? 4'b1000 : 4'b0100) :
                                                (loadstore_addr[0] ? 4'b0010 : 4'b0100)
                                            ):
                            mem_halfwordAccess ? (loadstore_addr[1] ? 4'b1100 : 4'b0011) :
                            4'b1111;

    always @(posedge clk) 
    begin
        if (resetn)
            begin
                PC <= 0;
            end 

        begin
            case (state)
                IF: begin
                    state <= IF_WAIT;
                end

                IF_WAIT: begin
                    if (PC == 0)
                        instr <= 32'b00000000000000000000000000000000;
                    else
                        instr <= mem_rdata;
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
                    state <= MM_WAIT; 
                end

                MM_WAIT: begin
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

    assign mem_addr = (state == IF) ? PC : loadstore_addr;
    assign rd_en = (state == IF || isLoad && state == MM);
    assign wmask = ({4{isStore}} & STORE_wmask);

    `ifdef BENCH
    //The following is bench portion interpreting the output
    always @(posedge clk)
    begin
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
                default: $display("ILLEGAL PC=%0d", PC);
            endcase

        if (isWB && state == WB)
            $display("Value written %h", WBData);
    end
    `endif

endmodule


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

    wire clk; //Internal clock (after slowing down)
    wire resetn; //Internal negative reset

    Clockworks #(.SLOW(15)) CW (CLK, RESET, clk, resetn);

    //Wires to connect processor and memory module and others
    wire [31:0] mem_addr;
    wire [31:0] mem_rdata;
    wire rd_en;

    wire [31:0] mem_wdata;
    wire [3:0] wmask;

    Memory RAM (clk, mem_addr, mem_rdata, rd_en, mem_wdata, wmask);

    Processor CPU (clk, resetn, mem_addr, mem_rdata, rd_en, mem_wdata, wmask);

    assign LEDS = 4'b1111;
    assign TXD = 1'b1;  //As always output 1 to UART

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