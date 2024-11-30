/*
 * list_algo_tests.c
 *
 * @project: ysyx
 * @author: Juntong Chen (dev@jtchen.io)
 * @created: 2024-11-14 20:18:49
 * @modified: 2024-11-30 00:13:53
 *
 * Copyright (c) 2024 Juntong Chen. All rights reserved.
 */

#include "minunit.h"
#include <lcthw/list_algos.h>
#include <assert.h>
#include <string.h>
#include <time.h>

#define NUM_VALUES 1000
char *values[NUM_VALUES];

static void load_values() {
    for (int i = 0; i < NUM_VALUES; i++) {
        values[i] = malloc(5);
        for (int j = 0; j < 4; j++) {
            values[i][j] = 'a' + rand() % 26;
        }
    }
}

List *create_words() {
    int i = 0;
    List *words = List_create();

    for (i = 0; i < NUM_VALUES; i++) {
        List_push(words, values[i]);
    }

    return words;
}

int is_sorted(List *words) {
    LIST_FOREACH(words, first, next, cur) {
        if (cur->next && strcmp(cur->value, cur->next->value) > 0) {
            debug("%s %s", (char *)cur->value, (char *)cur->next->value);
            return 0;
        }
    }
    return 1;
}

char *test_bubble_sort() {
    List *words = create_words();

    int rc = List_bubble_sort(words, (List_compare)strcmp);

    mu_assert(rc == 0, "Bubble sort failed.");
    mu_assert(is_sorted(words), "Words are not sorted after bubble sort.");

    // Should work on already sorted list
    rc = List_bubble_sort(words, (List_compare)strcmp);
    mu_assert(rc == 0, "Bubble sort of already sorted failed.");
    mu_assert(is_sorted(words), "Words should be sort if already bubble sorted.");

    List_destroy(words);

    // should work on an empty list
    words = List_create();
    rc = List_bubble_sort(words, (List_compare)strcmp);
    mu_assert(rc == 0, "Bubble sort failed on empty list.");
    mu_assert(is_sorted(words), "Words should be sorted if empty.");

    List_destroy(words);
    return NULL;
}

char *test_merge_sort() {
    List *words = create_words();

    List *res = List_merge_sort(words, (List_compare)strcmp);
    mu_assert(is_sorted(res), "Words are not sorted after merge sort.");

    List *res2 = List_merge_sort(res, (List_compare)strcmp);
    mu_assert(is_sorted(res), "Should still be sorted after merge sort.");
    List_destroy(res2);
    List_destroy(res);
    List_destroy(words);

    return NULL;
}

char *test_perf() {
    const int num_runs = 1e5 / NUM_VALUES;
    clock_t start, end;
    start = clock();
    for (int i = 0; i < num_runs; i++) {
        List * words = create_words();
        List_bubble_sort(words, (List_compare)strcmp);
        List_destroy(words);
    }
    end = clock();
    debug("Time elapsed for bubble sort: %ld ms", (end - start) / (CLOCKS_PER_SEC / 1000));
    start = clock();
    for (int i = 0; i < num_runs; i++) {
        List *words = create_words();
        List *res = List_merge_sort(words, (List_compare)strcmp);
        List_destroy(res);
        List_destroy(words);
    }
    end = clock();
    debug("Time elapsed for merge sort: %ld ms", (end - start) / (CLOCKS_PER_SEC / 1000));
    return NULL;
}

char *all_tests() {
    load_values();
    mu_suite_start();

    mu_run_test(test_bubble_sort);
    mu_run_test(test_merge_sort);
    mu_run_test(test_perf);

    return NULL;
}

RUN_TESTS(all_tests);