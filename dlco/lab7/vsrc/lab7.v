/*
 * top.v
 *
 * @project: ysyx
 * @author: Juntong Chen (dev@jtchen.io)
 * @created: 2024-12-21 00:39:23
 * @modified: 2024-12-21 16:48:33
 *
 * Copyright (c) 2024 Juntong Chen. All rights reserved.
 */
module lab7(
        input clrn,
        input clk,
        input ps2_clk,
        input ps2_data,
        output ready,
        output overflow,
        output pressed,
        output [7:0] data,
        output [7:0] seg7, seg6, seg5, seg4, seg3, seg2, seg1, seg0
    );

    ps2_keyboard ps2k(.clk(clk), .clrn(clrn), .ps2_clk(ps2_clk), .ps2_data(ps2_data),
                      .data(data), .ready(ready), .nextdata_n(ps2_data), .overflow(overflow));

    parameter [2:0] S0 = 0, S1 = 1, S2 = 2;
    reg [7:0] out_count;
    reg [2:0] state_dout, state_din;     // current state and next state
    reg state_en;                        // state machine enable

    SimReg #(3, S0) sm(.clk(clk), .reset(clrn), .state_din(state_din), .state_dout(state_dout), .state_en(state_en));

    // params: NR_KEY, KEY_LEN, DATA_LEN,
    MuxKeyWithDefault #(3, 3, 1) outMuxPressed(.out(pressed), .key(state_dout), .default_out(1'b0), .lut({
        S0, 1'b0,
        S1, 1'b1,
        S2, 1'b0
    }));

    always @(posedge ready) begin
        if (clrn == 1) begin
            out_count <= 0;
        end
        else begin
            state_en <= 1;
            // $display("data = %h",data);
            // handle state transition
            case(state_dout)
                S0: begin
                    if (data != 8'hF0) begin
                        state_din <= S1;
                    end
                    else begin
                        state_din <= S0;
                    end
                end
                S1: begin
                    if (data == 8'hF0) begin
                        state_din <= S2;
                    end
                    else begin
                        state_din <= S1;
                    end
                end
                S2: begin
                    state_din <= S0;
                    if (data != 8'h77)
                        out_count <= out_count + 1;
                end
                default: begin
                    state_din <= S0;
                end
            endcase
        end
    end

    assign seg5 = 8'b11111111;
    assign seg2 = 8'b11111111;

    // count
    wire [3:0] pa, pb;
    split_digit s1(.i(out_count), .a(pa), .b(pb));
    bcd7seq bs7(.b(pa), .h(seg7), .off(0), .dec(0));
    bcd7seq bs6(.b(pb), .h(seg6), .off(0), .dec(0));

    // key code
    wire [3:0] ka, kb;
    split_digit s2(.i(data), .a(ka), .b(kb));
    bcd7seq bs1(.b(ka), .h(seg1), .off(~pressed), .dec(0));
    bcd7seq bs0(.b(kb), .h(seg0), .off(~pressed), .dec(0));

    // ascii
    wire [3:0] aa, ab, ac;
    wire [7:0] ascii;
    ps2_scantoascii ps2s(.shift(0), .ctrl(0), .alt(0), .extend(0), .sc(data), .ascii(ascii));
    split_digit_3 s3(.i(ascii), .a(aa), .b(ab), .c(ac));
    bcd7seq bs5(.b(aa), .h(seg5), .off(~pressed), .dec(0));
    bcd7seq bs4(.b(ab), .h(seg4), .off(~pressed), .dec(0));
    bcd7seq bs3(.b(ac), .h(seg3), .off(~pressed), .dec(0));

endmodule

