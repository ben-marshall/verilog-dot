
module full_adder_1bit(
    input  a,
    input  b,
    input  cin,
    output sum,
    output carry
);

wire a_xor_b;

assign a_xor_b = a ^ b, sum=a_xor_b ^ cin;

assign carry   = (cin && a_xor_b) || (a && b);

endmodule



module adder_8bit(
    input  [7:0] a,
    input  [7:0] b,
    input  cin,
    output [7:0] sum,
    output carry
);

wire b0_carry;

full_adder_1bit b0(
    .a(a[0]),
    .b(b[0]),
    .cin(cin),
    .sum(sum[0]),
    .carry(b0_carry)
);


endmodule
