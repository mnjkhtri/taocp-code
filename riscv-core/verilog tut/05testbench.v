module tb_sample ();

    //Input signals to the sample simulation
    reg sim_clk;
    reg reset;
    reg [7:0] data_in;
    reg enable;

    //Output signals from the sample simulation
    wire [9:0] count;

    reg [31:0] random_num;  //To generate 32 bit random number and feed to vectors

    integer i;
    integer j;

    parameter CLK_PERIOD = 10;  //10ns
    parameter QUANT_VECTOR = 3200; //number of vector samples

    sim_sample mut (sim_clk, reset, data_in, enable, count);

    //CLOCK:
    //initial statement used exclusively in simulation modules
    initial sim_clk = 1'b0;
    always #(CLK_PERIOD/2.0)
        sim_clk = ~sim_clk;
    //# means wait for the time being in ns

    //RESET:
    initial reset = 1'b1;
    initial i = 0;  //As was declared integer earlier
    always @ (posedge sim_clk)
        begin
            i = i+1;
            if (i == 10)
                #1 reset <= 1'b0;   //To avoid timing issues
        end

    //Intials are actually blocks (like always) that are executed once
    //Multiple intial blocks operate simultaneously and each starts at time zero, once done it's over
    initial
    begin
        data_in = 8'b0;
        enable = 1'b0;

        //Wait until the reset goes active (other initials could run)
        wait (reset);
        //Then until low, thus waits upto the reset period as implied in reset portion
        wait (~reset);

        //After reset phase is done, we again wait for a bit of time
        @ (posedge sim_clk);
        for (j = 0; j < 10; j = j+1)
            begin
                @(posedge sim_clk);
            end

        //We are here as with the assertion of positive edge but enable is not yet high, so enable will have its effect from the nexzt cycle
        enable = 1'b1;
        $display("INITIAL COUNT = %d", count);  //Show the initial count
        @ (posedge sim_clk);    //Official first edge with enable activated;
        $display("FIRST COUNT = %d", count);  //Show the count, as it will be 1

        //FEED THE VECTORS:///////////////////////////////////////////////
        // for (j = 0; j < QUANT_VECTOR; j = j+1)
        //     begin
        //         random_num = $random;
        //         data_in = random_num[7:0];
        //         @ (posedge sim_clk);
        //         $display("COUNT = %d", count);
        //     end

        data_in = 8'h10;
        @ (posedge sim_clk);
        $display("COUNT = %d", count);

        data_in = 8'h10;
        @ (posedge sim_clk);
        $display("COUNT = %d", count);

        data_in = 8'h11;
        @ (posedge sim_clk);
        $display("COUNT = %d", count);
        ///////////////////////////////////////////////////////////////////

        //ENOUGH OF FEED:
        @(posedge sim_clk)
        enable = 1'b0;

        //To finish the simulation if necessary
        $finish;

        //Sometimes not letting the intial block to terminate with dummy work(for safety reasons)
        // forever
        //     begin
        //         @(posedge sim_clk) 
        //         enable = 1'b0;
        //     end
    end

    initial
        begin
            $dumpfile("testbench.vcd");
            $dumpvars(0,tb_sample);
        end
endmodule