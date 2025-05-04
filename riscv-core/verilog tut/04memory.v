//Dual port memory, one port for writes and another for reads
//Writes require write address and an write enable while read only needs read address

//1k*16bits memory (1024 16-bit words)
//Address size = lg(1024) = 10

module dp_mem(clk, reset, rd_en, wr_en, addr, data_in, data_out);

    input clk;
    input reset;

    input [9:0] addr;
    input wr_en;
    input rd_en;
    input [15:0] data_in;
    output [15:0] data_out;

    reg [15:0] memory[0:1023];
    reg [15:0] data_out;

    //The memory is to be implemented in RAM blocks but depends on synthesis software that converts verilog code into components
    always @ (posedge clk)
        begin
            if (wr_en)
                memory[addr] <= data_in;
            else if (rd_en)
                data_out <= memory[addr];
        end
    //The ordering of execution is maintained within begin - end block
    //While for multiple begin-end's the execution is indeterministic due to concurrency 
endmodule

//FPGA RAM blocks support multiple data ports and is the way to go
//Nevertheless single data port:

module single_port(clk, reset, rd_en, wr_en, addr, data_io);

    input clk;
    input reset;

    input [9:0] addr;
    input wr_en;
    input rd_en;
    inout [15:0] data_io;   //New declaration

    reg [15:0] memory[0:1023];
    reg [15:0] data_out;    //intermediate reg;

    always @ (posedge clk)
        begin
            if (wr_en)
                memory[addr] <= data_io;
            else if (rd_en)
                begin
                    data_out <= memory[addr];
                end
        end

    //Note this is not the part of the always block
    assign data_io = data_out;

endmodule