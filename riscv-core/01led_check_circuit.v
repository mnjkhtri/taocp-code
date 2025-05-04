//A LED counter that increases it's count at each clock edge (input and output as wires)
//Or fetches the LED pattern from memory and shows it
`include "clockworks.v"

module SOC (

    //System intput
    input CLK,
    input RESET,

    //LED output
    output [4:0] LEDS,

    //UART transmissions
    input RXD,
    output TXD

    );

    //Make a memory storage:
    reg [4:0] MEM [0:5];
    initial begin
        MEM[0] = 5'b00000;
        MEM[1] = 5'b00001;
        MEM[2] = 5'b00010;
        MEM[3] = 5'b00100;
        MEM[4] = 5'b01000;
        MEM[5] = 5'b10000;
    end

    wire clk; //Internal clock (after slowing down)
    wire resetn; //Internal negative reset

    Clockworks #(.SLOW(10)) CW (CLK, RESET, clk, resetn);

    reg [4:0] PC = 0;   //Used when fetching from memory
    reg [4:0] count;
    initial count = 0;
    always @(posedge clk)
        //Usual increment:
        //count <= (reset)? 0: count+1;

        //Memory fetch:
        begin
            count <= MEM[PC];
            PC <= (resetn || PC == 5) ? 0 : PC+1;
        end

    assign LEDS = count;
    assign TXD = 1'b0;

endmodule


//The bench module (not the actual hardware circuit), used for simulation only
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
    //Initially high then after a bit of time, goes low (ie unreset)
    initial begin RESET = 1'b1; #10 RESET = 1'b0; end 

    initial
    forever begin
        @(posedge CLK);
        $display("LEDS = %b", LEDS);
    end

endmodule