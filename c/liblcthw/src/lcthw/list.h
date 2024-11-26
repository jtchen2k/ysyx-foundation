/*
 * list.h
 *
 * @project: ysyx
 * @author: Juntong Chen (dev@jtchen.io)
 * @created: 2024-11-11 18:57:36
 * @modified: 2024-11-25 22:54:22
 *
 * Copyright (c) 2024 Juntong Chen. All rights reserved.
 */

#ifndef __LCTHW_LIST__
#define __LCTHW_LIST__

#include <stdlib.h>

struct ListNode;

typedef struct ListNode {
    struct ListNode *next;
    struct ListNode *prev;
    void *value;
} ListNode;

typedef struct List {
    int count;
    ListNode *first;
    ListNode *last;
} List;

List *List_create();
void List_destroy(List *list);
void List_clear(List *list);
void List_clear_destroy(List *list);

#define List_count(A) ((A->count))
#define List_first(A) ((A)->first != NULL ? (A)->first->value : NULL)
#define List_last(A) ((A)->last != NULL ? (A)->last->value : NULL)

void List_push(List *list, void *value);
void *List_pop(List *list);

void List_unshift(List *list, void *value);
void *List_shift(List* list);

void *List_remove(List *list, ListNode *node);

/**
 * A macro for iterating over a list.
 * L: list element
 * S: start element
 * M: next element
 * V: current element
 */
#define LIST_FOREACH(L, S, M, V) ListNode *_node = NULL;\
    ListNode *V = NULL;\
    for (V = _node = L->S; _node != NULL; V = _node = _node->M)


#endif /* __LCTHW_LIST__ */
