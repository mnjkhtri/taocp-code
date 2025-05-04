module dflop (clk, reset, enable, clear, in_1, out_1);

    input clk;      //clock signal
    input reset;    //global asynchronous signal
    input enable;   //enable
    input clear;    //synchronous clear

    //Regardness of enable, if clear is low, clears out

    input in_1;
    output out_1;

    //Also declare out_1 as a register (default is a wire)
    reg out_1;

    //To use always block to implement register logic
    //In contrast assign is continuously responsive

    //Only execute the block when the signals on the sensitivity list changes
    always @ (posedge clk or posedge reset)
        begin
            if (reset)
                out_1 <= 1'b0;  //1 for size of bus; b for radix and then actual value
            else if (clear == 1'b0)
                out_1 <= 1'b0;
            else if (enable)
                out_1 <= in_1;
        end 

endmodule

//Implement a four bit modulo 14 counter with start and stop pulse signals
//At start pulse, starts incrementing the counter, at stop pulse, stop the count
//At reset, clear the counter and stop the count

//Since the starts and stops are pulses and not continuous, need a SR flipflop to latch them

module srflop_cntr (clk, reset, start, stop, count);

    //Inout declarations
    input clk;
    input reset;
    input start;
    input stop;

    output [3:0] count;

    //Intermediates
    reg count_en;   //SR output, if start pulse hits, count_en = 1, if stop pulse hits, count_en = 0;

    //Type declarations
    reg [3:0] count;

    //SR flipflop block
    always @ (posedge clk or posedge reset)
        begin
            if (reset)
                count_en <= 1'b0;
            else if (start)
                count_en <= 1'b1;
            else if (stop)
                count_en <= 1'b0;
        end

    always @ (posedge clk or posedge reset)
        begin
            if (reset)
                count <= 4'h0;
            else if (count_en && count == 4'd13)
                count <= 4'h0;
            else if (count_en)
                count <= count + 1;
        end
endmodule