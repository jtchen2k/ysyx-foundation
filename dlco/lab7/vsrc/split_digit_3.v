/*
 * split_digit.v
 *
 * @project: ysyx
 * @author: Juntong Chen (dev@jtchen.io)
 * @created: 2024-12-21 14:35:44
 * @modified: 2024-12-21 15:19:02
 *
 * Copyright (c) 2024 Juntong Chen. All rights reserved.
 */

module split_digit_3(
    input [7:0] i,
    output [3:0] a,
    output [3:0] b,
    output [3:0] c
);
    wire [7:0] aa, bb, cc;
    assign aa = i / 8'd100;
    assign bb = (i % 8'd100) / 8'd10;
    assign cc = i % 8'd10;
    assign a = aa[3:0];
    assign b = bb[3:0];
    assign c = cc[3:0];
endmodule
