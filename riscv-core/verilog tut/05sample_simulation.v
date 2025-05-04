//A series of 8-bit words are checked to whether any two consecutive values are the same, and if found are tallied
//Last word is held in the register and compared with the first word of the next series

module sim_sample (clk, reset, data_in, enable, count);

    input clk;
    input reset;
    input [7:0] data_in;
    input enable;
    
    output [9:0] count;
    reg [9:0] count;

    reg[7:0] data_im;   //Intermediate data save

    always @ (posedge clk or posedge reset)
        begin
            if (reset)
                begin
                    data_im <= 8'h00;
                    count <= 10'd0;
                end
            else if (enable)
                begin
                    if (data_im == data_in)
                        count <= count + 1;
                    data_im <= data_in;
                end
        end

endmodule