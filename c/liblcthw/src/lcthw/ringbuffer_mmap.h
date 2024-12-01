/*
 * RingBufferM_mmap.h
 *
 * A ringbuffer implementation using mmap.
 *
 * @project: ysyx
 * @author: Juntong Chen (dev@jtchen.io)
 * @created: 2024-11-30 14:47:31
 * @modified: 2024-11-30 16:34:49
 *
 * Copyright (c) 2024 Juntong Chen. All rights reserved.
 */

#ifndef __LCTHW_RingBuffer_MMAP__
#define __LCTHW_RingBuffer_MMAP__

#include "lcthw/bstrlib.h"

typedef struct RingBufferM {
    char *buffer;
    int   length;
    int   read;
    int   write;
    int   _fd; // file descriptor to mapped file
    int   _sz; // size of mapped file, memory aligned,
} RingBufferM;

RingBufferM *RingBufferM_create(int length);

void RingBufferM_destroy(RingBufferM *buffer);

int RingBufferM_read(RingBufferM *buffer, char *target, int amount);

int RingBufferM_write(RingBufferM *buffer, char *data, int length);

int RingBufferM_empty(RingBufferM *buffer);

int RingBufferM_full(RingBufferM *buffer);

int RingBufferM_available_data(RingBufferM *buffer);

int RingBufferM_available_space(RingBufferM *buffer);

bstring RingBufferM_gets(RingBufferM *buffer, int amount);

#endif /* __LCTHW_RingBufferM_MMAP__ */