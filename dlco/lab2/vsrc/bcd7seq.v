/*
 * bcd7seq.v
 *
 * @project: ysyx
 * @author: Juntong Chen (dev@jtchen.io)
 * @created: 2024-12-04 23:18:42
 * @modified: 2024-12-04 23:48:50
 *
 * Copyright (c) 2024 Juntong Chen. All rights reserved.
 */
module bcd7seq(
        input [3:0] b,
        output reg [6:0] h
    );

    always @(*) begin
        case(b)
            4'd0:
                h = 7'b0000001;
            4'd1:
                h = 7'b1001111;
            4'd2:
                h = 7'b0010010;
            4'd3:
                h = 7'b0000110;
            4'd4:
                h = 7'b1001100;
            4'd5:
                h = 7'b0100100;
            4'd6:
                h = 7'b0100000;
            4'd7:
                h = 7'b0001111;
            4'd8:
                h = 7'b0000000;
            4'd9:
                h = 7'b0000100;
            default:
                h = 7'b1111111;
        endcase
    end

endmodule
