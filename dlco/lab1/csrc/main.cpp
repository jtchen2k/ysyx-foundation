/*
 * main.cpp
 *
 * @project: ysyx
 * @author: Juntong Chen (dev@jtchen.io)
 * @created: 2024-12-01 19:42:35
 * @modified: 2024-12-01 21:51:24
 *
 * Copyright (c) 2024 Juntong Chen. All rights reserved.
 */

#include "Vmux412.h"
#include <cassert>
#include <cstdio>
#include <nvboard.h>
#include <verilated.h>
#include <verilated_vcd_c.h>

#ifndef TOP_NAME
#define TOP_NAME Vmux412
#endif

static VerilatedVcdC    *g_trace;
static VerilatedContext *g_context;
static TOP_NAME         *dut;
static int               TRACE_DUMP_CYCLE = 1e3;
static int               TRACE_FLUSH_CYCLE = 1e6;
static bool              TRACE_ON = false;

void nvboard_bind_all_pins(TOP_NAME *top);

static void single_cycle_trace() {
    auto cur_cycle = g_context->time();
    if (cur_cycle % TRACE_DUMP_CYCLE == 0)
        g_trace->dump(cur_cycle);
    if (cur_cycle % TRACE_FLUSH_CYCLE == 0) {
        g_trace->flush();
        printf("saved trace. cur_cycle = %ld\n", g_context->time());
    }
}

static void single_cycle() {
    g_context->timeInc(1);
    dut->eval();
    if (TRACE_ON)
        single_cycle_trace();
}

static void setup_trace() {
    if (!TRACE_ON)
        return;
    Verilated::traceEverOn(true);
    dut->trace(g_trace, 99);
    g_trace->open("waveform.fsd");
}

static void setup_dut() {
    g_context = new VerilatedContext();
    g_trace = new VerilatedVcdC();
    dut = new TOP_NAME(g_context);

    dut->x0 = 3;
    dut->x1 = 2;
    dut->x2 = 1;
    dut->x3 = 0;
}

int main() {
    setup_dut();
    setup_trace();

    nvboard_bind_all_pins(dut);
    nvboard_init();
    while (1) {
        nvboard_update();
        single_cycle();
    }
    return 0;
}
