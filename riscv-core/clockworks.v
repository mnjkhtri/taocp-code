//Takes in the clock and slows it down by 2^SLOW (SLOW passed from instantiation)

module Clockworks 
(
    input  CLK, 
    input  RESET,
    output clk,
    output resetn //(to be used internally)
);

    /////////////////////////////////////////////////////////////////////
    //Passed from instantiation
    parameter SLOW = 0; //0 by default

    //Internal slow mechanics
    reg [SLOW:0] slow_CLK = 0;
    always @(posedge CLK) begin
        slow_CLK <= slow_CLK + 1;
    end
    assign clk = slow_CLK[SLOW];

    //Internal reset mechanisms
    assign resetn = RESET;
    /////////////////////////////////////////////////////////////////////

endmodule