/*
 * encode83.v
 *
 * @project: ysyx
 * @author: Juntong Chen (dev@jtchen.io)
 * @created: 2024-12-04 22:41:46
 * @modified: 2024-12-04 23:52:24
 *
 * Copyright (c) 2024 Juntong Chen. All rights reserved.
 */

module encode83 (
        input [7:0] x,
        input en,
        output reg [7:0] seg,
        output reg [3:0] y,
        output reg z
    );
    integer i;
    always @(x, en) begin
        seg[0] = 1;
        if (en) begin
            y = 0;
            z = 0;
            for (i = 0; i < 8; i = i + 1) begin
                if (x[i] == 1) begin
                    y = i[3:0];
                    z = 1;
                end
            end
        end
        else begin
            y = 0;
            z = 0;
        end
    end
    bcd7seq ins1 (.b(y), .h(seg[7:1]));
endmodule
