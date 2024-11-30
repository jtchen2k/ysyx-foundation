/*
 * ringbuffer_tests.c
 *
 * @project: ysyx
 * @author: Juntong Chen (dev@jtchen.io)
 * @created: 2024-11-30 00:04:53
 * @modified: 2024-11-30 01:33:43
 *
 * Copyright (c) 2024 Juntong Chen. All rights reserved.
 */

#include "minunit.h"
#include <assert.h>
#include <lcthw/ringbuffer.h>

char *test_create() {
    RingBuffer *buffer1 = RingBuffer_create(10); // expect success
    RingBuffer *buffer2 = RingBuffer_create(0);  // expect fail
    mu_assert(RingBuffer_empty(buffer1), "Failed to create buffer.");
    mu_assert(RingBuffer_available_space(buffer1) == 10, "Wrong buffer size.");
    mu_assert(RingBuffer_available_data(buffer1) == 0, "Wrong data size.");
    mu_assert(buffer2 == NULL, "Should not create buffer with size 0.");
    return NULL;
}

char *test_read_write() {
    RingBuffer *buffer = RingBuffer_create(20);
    char       *data = "Hello, world";
    RingBuffer_write(buffer, data, 12);
    mu_assert(RingBuffer_available_data(buffer) == 12, "Wrong available data size.");
    mu_assert(RingBuffer_available_space(buffer) == 8, "Wrong available space size.");
    char *res = calloc(20, 1);
    RingBuffer_read(buffer, res, 5);
    mu_assert(strcmp(res, "Hello") == 0, "Wrong read data.");
    mu_assert(RingBuffer_available_data(buffer) == 7, "Wrong available data size.");
    mu_assert(RingBuffer_available_space(buffer) == 8, "Wrong available space size.");

    RingBuffer_write(buffer, data, 12); // expect fail

    // read till empty. will cause start and end to be reset to 0.
    RingBuffer_read(buffer, res, 7);
    mu_assert(strcmp(res, ", world") == 0, "Wrong read data.");
    mu_assert(RingBuffer_available_data(buffer) == 0, "Wrong available data size.");

    RingBuffer_write(buffer, data, 12);
    mu_assert(RingBuffer_available_data(buffer) == 12, "Wrong available data size.");

    RingBuffer *b1 = RingBuffer_create(10);
    b1->start = 7;
    b1->end = 2;
    mu_assert(RingBuffer_available_data(b1) == 5, "Wrong available data size.");

    return NULL;
}

char *test_destroy() {
    RingBuffer *buffer = RingBuffer_create(10);
    RingBuffer_destroy(buffer);
    mu_assert(RingBuffer_available_data(buffer) == 0, "Failed to destroy buffer.");
    return NULL;
}

char *all_tests() {
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_read_write);
    mu_run_test(test_destroy);

    return NULL;
}

RUN_TESTS(all_tests);