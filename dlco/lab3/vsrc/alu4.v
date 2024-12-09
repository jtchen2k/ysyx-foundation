/*
 * alu4.v
 *
 * @project: ysyx
 * @author: Juntong Chen (dev@jtchen.io)
 * @created: 2024-12-05 00:11:47
 * @modified: 2024-12-08 22:36:26
 *
 * Copyright (c) 2024 Juntong Chen. All rights reserved.
 */

module alu4 (input [3:0] a, b,
                 [2:0] op,
                 output reg [3:0] out);
    always @(*) begin
        case (op)
            3'b000:
                out = a + b;
            3'b001:
                out = a - b;
            3'b010:
                out = ~a;
            3'b011:
                out = a & b;
            3'b100:
                out = a | b;
            3'b101:
                out = a ^ b;
            3'b110:
                out = a < b ? 4'b0001 : 4'b0000;
            3'b111:
                out = a == b ? 4'b0001 : 4'b0000;
            default:
                out = 4'b1111;
        endcase
    end
endmodule
