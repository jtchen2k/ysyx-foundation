/*
 * ringbuffer_mmap.c
 *
 * @project: ysyx
 * @author: Juntong Chen (dev@jtchen.io)
 * @created: 2024-11-30 14:57:05
 * @modified: 2024-11-30 20:48:37
 *
 * Copyright (c) 2024 Juntong Chen. All rights reserved.
 */

#include "ringbuffer_mmap.h"
#include "dbg.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/syscall.h>
#include <unistd.h>

RingBufferM *RingBufferM_create(int length) {
    RingBufferM *buffer = calloc(1, sizeof(RingBufferM));
    buffer->length = length + 1;
    buffer->read = 0;
    buffer->write = 0;
    int res = 0;

    long pagesize = getpagesize();
    long sz = (buffer->length + pagesize - 1) / pagesize * pagesize;
    int  fd = fileno(tmpfile());
    check(fd >= 0, "Failed to create temporary file.");
    check(ftruncate(fd, sz) == 0, "Failed to allocate ring buffer.");
    debug("RingBufferM_create: fd=%d, sz=%ld", fd, sz);

    buffer->_fd = fd;
    buffer->_sz = sz;
    buffer->buffer = mmap(NULL, 2 * sz, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    check(buffer->buffer != MAP_FAILED, "Failed to create mmap buffer.");

    void *address;
    address = mmap(buffer->buffer, sz, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_FIXED, fd, 0);
    check(address == buffer->buffer, "Failed to mmap buffer [0, sz).");
    address = mmap(buffer->buffer + sz, sz, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_FIXED, fd, 0);
    check(address == buffer->buffer + sz, "Failed to mmap buffer sz -> [sz, 2 * sz).");
    return buffer;

error:
    return NULL;
}

void RingBufferM_destroy(RingBufferM *buffer) {
    if (buffer) {
        munmap(buffer->buffer, 2 * buffer->_sz);
        check(ftruncate(buffer->_fd, 0) == 0, "Failed to truncate file.");
        close(buffer->_fd);
        free(buffer);
    }

error:
    return;
}

inline int RingBufferM_available_data(RingBufferM *buffer) {
    return (buffer->write - buffer->read + buffer->length) % buffer->length;
}

// always leave one byte empty to distinguish full and empty
inline int RingBufferM_available_space(RingBufferM *buffer) {
    return buffer->length - RingBufferM_available_data(buffer) - 1;
}

inline int RingBufferM_full(RingBufferM *buffer) {
    return RingBufferM_available_space(buffer) == 0;
}

inline int RingBufferM_empty(RingBufferM *buffer) {
    return RingBufferM_available_data(buffer) == 0;
}

inline int RingBufferM_size(RingBufferM *buffer) { return buffer->length - 1; }

int RingBufferM_write(RingBufferM *buffer, char *data, int length) {
    check(length <= RingBufferM_available_space(buffer),
          "Not enough space: %d request, %d available", length,
          RingBufferM_available_space(buffer));

    void *res = memcpy(buffer->buffer + buffer->write, data, length);
    check(res != NULL, "Failed to write data into buffer.");
    buffer->write = (buffer->write + length) % buffer->length;
    return 0;
error:
    return -1;
}

int RingBufferM_read(RingBufferM *buffer, char *target, int amount) {
    check(amount <= RingBufferM_available_data(buffer),
          "Not enough in the buffer: has %d, needs %d", RingBufferM_available_data(buffer), amount);

    void *res = memcpy(target, buffer->buffer + buffer->read, amount);
    check(res != NULL, "Failed to write buffer into data.");

    buffer->read = (buffer->read + amount) % buffer->length;
    return 0;
error:
    return -1;
}

bstring RingBufferM_gets(RingBufferM *buffer, int amount) {
    check(amount > 0, "Need more than 0 for gets, you gave %d", amount);
    check(amount <= RingBufferM_available_data(buffer), "Not enough in the buffer.");
    char *data = calloc(amount, 1);
    check_mem(data);

    RingBufferM_read(buffer, data, amount);
    bstring result = blk2bstr(data, amount);
    check(result != NULL, "Failed to create gets result.");
    check(blength(result) == amount, "Wrong result length.");

    return result;
error:
    return NULL;
}