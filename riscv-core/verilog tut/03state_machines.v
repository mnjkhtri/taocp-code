//A state machine with four internal states namely idle, active, finish and abort
//With go signal, enters active, counts upto 1000 and then goes finish where asserts done signal to output
//Unless it's interrupted with kill input signal in active then aborts untill kill is high

module state_machine (clk, reset, go, kill, done);

    input clk;
    input reset;
    input go;
    input kill;
    
    output done;
    reg done;

    reg [1:0] state;      //To implement the current state  
    reg [6:0] count;      //To count while in active state

    //Local parameters for alphanumeric mapping, on the other hand, define is global
    parameter idle = 2'b00;
    parameter active = 2'b01;
    parameter finish = 2'b10;
    parameter abort = 2'b11;

    //State machine
    always @ (posedge clk or posedge reset)
        begin
            if (reset)
                state <= idle;
            else
                case (state)
                    idle:
                        if (go) state <= active;
                    active:
                        if (kill) state <= abort;
                        else if (count == 7'd100) state <= finish;
                    finish:
                        state <= idle;
                    abort:
                        if (!kill) state <= idle;
                    default:
                        state <= idle;
                endcase
        end

    //Counter
    always @ (posedge clk or posedge reset)
        begin
            if (reset)
                count <= 7'h00;
            else if (state == finish || state == abort)
                count <= 7'h00;
            else if (state == active)
                count <= count + 1;
        end

    //Done register
    always @ (posedge clk or posedge reset)
        begin
            if (reset)
                done <= 1'b0;
            else if (state == finish)
                done <= 1'b1;
            else
                done <= 1'b0;
        end

endmodule


//Modular design

module instant_machines(clk, reset, go, kill, done);

    input clk, reset, go, kill;

    output done;

    //Does continuous assignment to the signals (so registers are not allowed directly)
    state_machine machine1(clk, reset, go, kill, done);

endmodule