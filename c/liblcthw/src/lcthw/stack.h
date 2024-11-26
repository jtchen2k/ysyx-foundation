/*
 * stack.h
 *
 * @project: ysyx
 * @author: Juntong Chen (dev@jtchen.io)
 * @created: 2024-11-25 22:43:58
 * @modified: 2024-11-25 23:11:50
 *
 * Copyright (c) 2024 Juntong Chen. All rights reserved.
 */

#ifndef __LCTHW_STACK__
#define __LCTHW_STACK__

#include "list.h"

#define Stack List
#define Stack_create() List_create()
#define Stack_destroy(A) List_destroy(A)
#define Stack_count(A) List_count(A)
#define Stack_peek(A) List_last(A)
#define Stack_push(A, V) List_push(A, V)
#define Stack_pop(A) List_pop(A)
#define Stack_destroy(A) List_destroy(A)

#define STACK_FOREACH(L, C) LIST_FOREACH(L, first, next, C)

#endif /* __LCTHW_STACK__ */
