/*
 * list_algos.h
 * Project: lcthw
 * Created: 2024-11-14 20:06:46
 * Author: Juntong Chen (dev@jtchen.io)
 * -----
 * Last Modified: 2024-11-14 22:01:22
 * Modified By: Juntong Chen (dev@jtchen.io)
 */

#ifndef YSYX_FOUNDATION_C_LIBLCTHW_SRC_LCTHW_LIST_ALGOS
#define YSYX_FOUNDATION_C_LIBLCTHW_SRC_LCTHW_LIST_ALGOS

#include <lcthw/list.h>

typedef int (*List_compare)(const void *s1, const void *s2);

int List_bubble_sort(List *list, List_compare cmp);

List *List_merge_sort(List *list, List_compare cmp);

#endif /* YSYX_FOUNDATION_C_LIBLCTHW_SRC_LCTHW_LIST_ALGOS */
