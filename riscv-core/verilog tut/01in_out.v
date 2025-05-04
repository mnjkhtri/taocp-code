module in_out_module (in_1, in_2, out_1, out_2);

   //Input ports
   input in_1;
   input in_2;

   //Output ports
   output out_1;
   output out_2;

   //Assignments
   assign out_1 = in_1 & in_2;
   assign out_2 = in_1 | in_2;

endmodule

module intermediate (in_1, in_2, out_1);

   input in_1;
   input in_2;
   
   output out_1;

   //Intermediate signals
   wire intermezzo;

   assign intermezzo = in_1 & in_2;
   assign out_1 = intermezzo | in_2;

endmodule

module buses (in_1, in_2, in_3, out_1);

   //For declaring a bus with bits from 0 to 3 (total = 4)
   input [3:0] in_1;
   input [3:0] in_2;
   input in_3;
   
   output [3:0] out_1;

   wire [3:0] intermezzo;

   //For assigning a single bit to a bus
   assign intermezzo = {4{in_3}};

   //Does bitwise assignment
   assign out_1 = (intermezzo & in_1) | (in_1 & in_2);

endmodule

module morebuses (in_1, in_2, in_3, out_1, out_2);

   input [3:0] in_1, in_2;
   input in_3;

   output [3:0] out_1;
   output [5:0] out_2;

   //Ternary bitwise operator   
   assign out_1 = in_3 ? in_1 : in_2;
   //Concatenation
   assign out_2 = {in_1[1:0], (in_2[3:0] & in_1[4:1])};

endmodule
