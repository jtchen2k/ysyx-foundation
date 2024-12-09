/*
 * rand8.v
 *
 * @project: ysyx
 * @author: Juntong Chen (dev@jtchen.io)
 * @created: 2024-12-08 23:13:37
 * @modified: 2024-12-08 23:19:47
 *
 * Copyright (c) 2024 Juntong Chen. All rights reserved.
 */

module rand8 (
        input wire clk,
        output reg [7:0] x
    );

    always @(posedge clk) begin
        if ( |x == 0) begin
            x <= 8'b1;
        end
        else begin
            x <= {x[4] ^ x[3] ^ x[2] ^ x[0], x[7:1]};
        end
    end

endmodule
