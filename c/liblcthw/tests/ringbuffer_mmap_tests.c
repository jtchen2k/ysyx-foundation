/*
 * ringbuffer_mmap_tests.c
 *
 * @project: ysyx
 * @author: Juntong Chen (dev@jtchen.io)
 * @created: 2024-11-30 14:54:38
 * @modified: 2024-11-30 21:11:36
 *
 * Copyright (c) 2024 Juntong Chen. All rights reserved.
 */

#include "lcthw/ringbuffer.h"
#include "lcthw/ringbuffer_mmap.h"
#include "minunit.h"
#include <string.h>
#include <time.h>

const static int DATA_SIZE = 3000;
const static int BUFFER_SIZE = DATA_SIZE * 4;
const static int TEST_COUNT = 3e6;

char *data_a;
char *data_b;

static void init_data() {
    data_a = calloc(DATA_SIZE, 1);
    data_b = calloc(DATA_SIZE, 1);
    for (int i = 0; i < DATA_SIZE; i++) {
        data_a[i] = 'a';
        data_b[i] = 'b';
    }
}

char *test_create() {
    RingBufferM *buffer = RingBufferM_create(BUFFER_SIZE);
    mu_assert(buffer != NULL, "Failed to create buffer.");
    mu_assert(RingBufferM_empty(buffer), "Failed to create buffer.");
    mu_assert(RingBufferM_available_space(buffer) == BUFFER_SIZE, "Wrong buffer size.");
    mu_assert(RingBufferM_available_data(buffer) == 0, "Wrong data size.");
    return NULL;
}

char *test_read_write() {
    // sequence: write a, write b, read a, read b. repeat TEST_COUNT times;
    RingBufferM *buffer = RingBufferM_create(BUFFER_SIZE);
    int          n = 100;
    while (n--) {
        RingBufferM_write(buffer, data_a, DATA_SIZE);
        mu_assert(RingBufferM_available_data(buffer) == DATA_SIZE, "Wrong available data size.");
        mu_assert(RingBufferM_available_space(buffer) == BUFFER_SIZE - DATA_SIZE,
                  "Wrong available space size.");

        RingBufferM_write(buffer, data_b, DATA_SIZE);
        mu_assert(RingBufferM_available_data(buffer) == DATA_SIZE * 2,
                  "Wrong available data size.");
        mu_assert(RingBufferM_available_space(buffer) == BUFFER_SIZE - DATA_SIZE * 2,
                  "Wrong available space size.");

        char *res = calloc(DATA_SIZE + 1, 1);
        RingBufferM_read(buffer, res, DATA_SIZE);
        mu_assert(RingBufferM_available_data(buffer) == DATA_SIZE, "Wrong available data size.");
        mu_assert(RingBufferM_available_space(buffer) == BUFFER_SIZE - DATA_SIZE,
                  "Wrong available space size.");
        mu_assert(strncmp(res, data_a, DATA_SIZE) == 0, "Wrong read data using read.");

        bstring bres = RingBufferM_gets(buffer, DATA_SIZE);
        mu_assert(RingBufferM_available_data(buffer) == 0, "Wrong available data size.");
        mu_assert(RingBufferM_available_space(buffer) == BUFFER_SIZE,
                  "Wrong available space size.");
        mu_assert(biseqblk(bres, data_b, DATA_SIZE) == 1, "Wrong read data using bstring gets.");
    }
    return NULL;
}

char *test_destroy() {
    RingBufferM *buffer = RingBufferM_create(BUFFER_SIZE);
    RingBufferM_destroy(buffer);
    return NULL;
}

char *test_perf_mmap() {
    RingBufferM *buffer_mmp = RingBufferM_create(BUFFER_SIZE);
    clock_t      start, end;
    double       duration_array = 0, duration_mmp = 0;
    int          n = TEST_COUNT;
    char        *res = calloc(DATA_SIZE, 1);
    while (n--) {
        start = clock();
        RingBufferM_write(buffer_mmp, data_a, DATA_SIZE);
        RingBufferM_write(buffer_mmp, data_b, DATA_SIZE / 4);
        RingBufferM_write(buffer_mmp, data_a, DATA_SIZE / 2);
        RingBufferM_write(buffer_mmp, data_b, DATA_SIZE / 2);
        RingBufferM_read(buffer_mmp, res, DATA_SIZE / 2);
        RingBufferM_read(buffer_mmp, res, DATA_SIZE / 2);
        RingBufferM_read(buffer_mmp, res, DATA_SIZE / 4);
        RingBufferM_read(buffer_mmp, res, DATA_SIZE);
        end = clock();
        duration_mmp += (double)(end - start) * 1000 / CLOCKS_PER_SEC;
    }
    log_info("RingBuffer using mmap: %f ms", duration_mmp);
    return NULL;
}

char *test_perf_array() {
    RingBuffer *buffer_array = RingBuffer_create(BUFFER_SIZE);
    clock_t     start, end;
    double      duration_array = 0, duration_mmp = 0;
    int         n = TEST_COUNT;
    char       *res = calloc(DATA_SIZE, 1);
    while (n--) {
        start = clock();
        RingBuffer_write(buffer_array, data_a, DATA_SIZE);
        RingBuffer_write(buffer_array, data_b, DATA_SIZE / 4);
        RingBuffer_write(buffer_array, data_a, DATA_SIZE / 2);
        RingBuffer_write(buffer_array, data_b, DATA_SIZE / 2);
        RingBuffer_read(buffer_array, res, DATA_SIZE / 2);
        RingBuffer_read(buffer_array, res, DATA_SIZE / 2);
        RingBuffer_read(buffer_array, res, DATA_SIZE / 4);
        RingBuffer_read(buffer_array, res, DATA_SIZE);
        end = clock();
        duration_array += (double)(end - start) * 1000 / CLOCKS_PER_SEC;
    }
    log_info("RingBuffer using array: %f ms", duration_array);
    return NULL;
}

char *all_tests() {
    mu_suite_start();

    init_data();

    mu_run_test(test_create);
    mu_run_test(test_read_write);
    mu_run_test(test_destroy);
    mu_run_test(test_perf_mmap);
    mu_run_test(test_perf_array);

    return NULL;
}

RUN_TESTS(all_tests);