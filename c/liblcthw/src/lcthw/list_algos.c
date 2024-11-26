/*
 * list_algos.c
 *
 * @project: ysyx
 * @author: Juntong Chen (dev@jtchen.io)
 * @created: 2024-11-14 20:07:17
 * @modified: 2024-11-25 22:54:22
 *
 * Copyright (c) 2024 Juntong Chen. All rights reserved.
 */

#include <lcthw/list_algos.h>

/*
procedure bubbleSort(A : list of sortable items)
    n := length(A)
    repeat
        swapped := false
        for i := 1 to n-1 inclusive do
            { if this pair is out of order }
            if A[i-1] > A[i] then
                { swap them and remember something changed }
                swap(A[i-1], A[i])
                swapped := true
            end if
        end for
    until not swapped
end procedure
*/
int List_bubble_sort(List *list, List_compare cmp) {
    if (List_count(list) <= 1)
        return 0;
    int swapped = 0;
    do {
        swapped = 0;
        LIST_FOREACH(list, first, next, cur) {
            if (cur->next && cmp(cur->value, cur->next->value) > 0) {
                void* tmp = cur->value;
                cur->value = cur->next->value;
                cur->next->value = tmp;
                swapped = 1;
            }
        }
    } while (swapped);
    return 0;
}

/*

function merge_sort(list m) is
    // Base case. A list of zero or one elements is sorted, by definition.
    if length of m ≤ 1 then
        return m

    // Recursive case. First, divide the list into equal-sized sublists
    // consisting of the first half and second half of the list.
    // This assumes lists start at index 0.
    var left := empty list
    var right := empty list
    for each x with index i in m do
        if i < (length of m)/2 then
            add x to left
        else
            add x to right
    // Recursively sort both sublists.
    left := merge_sort(left)
    right := merge_sort(right)

    // Then merge the now-sorted sublists.
    return merge(left, right)

function merge(left, right) is
    var result := empty list

    while left is not empty and right is not empty do
        if first(left) ≤ first(right) then
            append first(left) to result
            left := rest(left)
        else
            append first(right) to result
            right := rest(right)

    // Either left or right may have elements left; consume them.
    // (Only one of the following loops will actually be entered.)
    while left is not empty do
        append first(left) to result
        left := rest(left)
    while right is not empty do
        append first(right) to result
        right := rest(right)
    return result
*/
List *List_merge(List *left, List *right, List_compare cmp) {
    List* res = List_create();

    while (List_count(left) > 0 && List_count(right) > 0) {
        if (cmp(left->first->value, right->first->value) <= 0) {
            List_push(res, List_shift(left));
        } else {
            List_push(res, List_shift(right));
        }
    }
    while (List_count(left) > 0) {
        List_push(res, List_shift(left));
    }
    while (List_count(right) > 0) {
        List_push(res, List_shift(right));
    }
    return res;
}

List *List_merge_sort(List *list, List_compare cmp) {
    if (List_count(list) <= 1) return list;

    List* left = List_create();
    List* right = List_create();
    int cnt = List_count(list);
    for (int i = 0; i < cnt; i++) {
        if (i < cnt / 2) List_push(left, List_shift(list));
        else List_push(right, List_shift(list));
    }

    left = List_merge_sort(left, cmp);
    right = List_merge_sort(right, cmp);

    return List_merge(left, right, cmp);
}