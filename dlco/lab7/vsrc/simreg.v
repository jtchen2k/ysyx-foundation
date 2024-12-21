/*
 * simreg.v
 *
 * @project: ysyx
 * @author: Juntong Chen (dev@jtchen.io)
 * @created: 2024-12-20 23:03:51
 * @modified: 2024-12-20 23:05:56
 *
 * Copyright (c) 2024 Juntong Chen. All rights reserved.
 */
module SimReg #(
    parameter WIDTH = 4,
    parameter RESET_VALUE = 0
) (
    input clk,
    input reset,
    input [WIDTH-1:0] state_din,
    output reg [WIDTH-1:0] state_dout,
    input state_en
);
    always @(posedge clk) begin
        if (reset) begin
            state_dout <= RESET_VALUE;
        end
        else if (state_en) begin
            state_dout <= state_din;
        end
    end

endmodule