/*
 * queue.h
 *
 * @project: ysyx
 * @author: Juntong Chen (dev@jtchen.io)
 * @created: 2024-11-25 22:51:09
 * @modified: 2024-11-26 16:27:47
 *
 * Copyright (c) 2024 Juntong Chen. All rights reserved.
 */

#ifndef __LCTHW_QUEUE__
#define __LCTHW_QUEUE__

#include "list.h"

#define Queue List
#define Queue_create() List_create()
#define Queue_destroy(A) List_destroy(A)
#define Queue_count(A) List_count(A)
#define Queue_peek(A) List_first(A)
#define Queue_send(A, V) List_push(A, V)
#define Queue_recv(A) List_shift(A)
#define Queue_destroy(A) List_destroy(A)

#define QUEUE_FOREACH(L, C) LIST_FOREACH(L, first, next, C)

#endif /* __LCTHW_QUEUE__ */
