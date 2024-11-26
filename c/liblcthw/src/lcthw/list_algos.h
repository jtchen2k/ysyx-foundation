/*
 * list_algos.h
 *
 * @project: ysyx
 * @author: Juntong Chen (dev@jtchen.io)
 * @created: 2024-11-14 20:06:46
 * @modified: 2024-11-25 22:54:22
 *
 * Copyright (c) 2024 Juntong Chen. All rights reserved.
 */

#ifndef __LCTHW_LIST_ALGOS__
#define __LCTHW_LIST_ALGOS__

#include <lcthw/list.h>

typedef int (*List_compare)(const void *s1, const void *s2);

int List_bubble_sort(List *list, List_compare cmp);

List *List_merge_sort(List *list, List_compare cmp);

#endif /* __LCTHW_LIST_ALGOS__ */
