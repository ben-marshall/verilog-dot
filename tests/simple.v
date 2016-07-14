
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
