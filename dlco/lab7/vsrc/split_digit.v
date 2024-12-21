/*
 * split_digit.v
 *
 * @project: ysyx
 * @author: Juntong Chen (dev@jtchen.io)
 * @created: 2024-12-21 14:35:44
 * @modified: 2024-12-21 14:35:52
 *
 * Copyright (c) 2024 Juntong Chen. All rights reserved.
 */

module split_digit(
    input [7:0] i,
    output [3:0] a,
    output [3:0] b
);
    wire [7:0] high, low;
    assign high = i / 8'd10;
    assign low = i % 8'd10;
    assign a = high[3:0];
    assign b = low[3:0];
endmodule
