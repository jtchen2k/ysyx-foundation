/*
 * bcd7seq.v
 *
 * @project: ysyx
 * @author: Juntong Chen (dev@jtchen.io)
 * @created: 2024-12-05 00:11:47
 * @modified: 2024-12-21 15:03:57
 *
 * Copyright (c) 2024 Juntong Chen. All rights reserved.
 */

module bcd7seq(
        input [3:0] b,
        input dec,
        input off,
        output reg [7:0] h
    );

    always @(*) begin
        case(b)
            4'd0:
                h = 8'b00000011;
            4'd1:
                h = 8'b10011111;
            4'd2:
                h = 8'b00100101;
            4'd3:
                h = 8'b00001101;
            4'd4:
                h = 8'b10011001;
            4'd5:
                h = 8'b01001001;
            4'd6:
                h = 8'b01000001;
            4'd7:
                h = 8'b00011111;
            4'd8:
                h = 8'b00000001;
            4'd9:
                h = 8'b00001001;
            default:
                h = 8'b11111111;
        endcase
        if (dec) begin
            h = h | 8'b11111110;
        end
        if (off) begin
            h = 8'b11111111;
        end
    end
endmodule
