/*
 * bstr_tests.c
 *
 * @project: ysyx
 * @author: Juntong Chen (dev@jtchen.io)
 * @created: 2024-11-29 22:35:38
 * @modified: 2024-11-29 23:28:37
 *
 * Copyright (c) 2024 Juntong Chen. All rights reserved.
 */

#include "minunit.h"
#include <assert.h>
#include <lcthw/bstrlib.h>

char *test_bfromcstr() {
    char   *test_string = "hello";
    bstring b = bfromcstr(test_string);
    mu_assert(b->slen == 5, "Wrong length.");
    for (int i = 0; i < 5; i++) {
        mu_assert(b->data[i] == test_string[i], "Wrong character.");
    }
    return NULL;
}

char *test_blk2bstr() {
    char   *test_string = "hello";
    bstring b = blk2bstr(test_string, 5);
    mu_assert(b->slen == 5, "Wrong length.");
    for (int i = 0; i < 5; i++) {
        mu_assert(b->data[i] == test_string[i], "Wrong character.");
    }
    return NULL;
}

char *test_bstrcpy() {
    char   *test_string = "hello";
    bstring b = bfromcstr(test_string);
    bstring c = bstrcpy(b);
    mu_assert(b->slen == c->slen, "Wrong length.");
    for (int i = 0; i < 5; i++) {
        mu_assert(b->data[i] == c->data[i], "Wrong character.");
    }
    return NULL;
}

char *test_bassign() {
    char *sa = "hello", *sb = "world";
    bstring ba = bfromcstr(sa);
    bstring bb = bfromcstr(sb);
    bassign(ba, bb);
    mu_assert(ba->slen == 5, "Wrong length.");
    for (int i = 0; i < 5; i++) {
        mu_assert(ba->data[i] == sb[i], "Wrong character.");
    }
    return NULL;
}

char *test_bassigncstr() {
    char *sa = "hello", *sb = "world";
    bstring ba = bfromcstr(sa);
    bassigncstr(ba, sb);
    mu_assert(ba->slen == 5, "Wrong length.");
    for (int i = 0; i < 5; i++) {
        mu_assert(ba->data[i] == sb[i], "Wrong character.");
    }
    return NULL;
}

char *test_bassignblk() {
    char *sa = "hello", *sb = "world";
    bstring ba = bfromcstr(sa);
    bassignblk(ba, sb, 5);
    mu_assert(ba->slen == 5, "Wrong length.");
    for (int i = 0; i < 5; i++) {
        mu_assert(ba->data[i] == sb[i], "Wrong character.");
    }
    return NULL;
}

char *test_bdestroy() {
    char *sa = "hello";
    bstring ba = bfromcstr(sa);
    mu_assert(bdestroy(ba) == BSTR_OK, "Should be BSTR_OK.");
    return NULL;
}

char *test_bconcat() {
    char *sa = "hello", *sb = "world";
    bstring ba = bfromcstr(sa);
    bstring bb = bfromcstr(sb);
    bconcat(ba, bb);
    mu_assert(ba->slen == 10, "Wrong length.");
    for (int i = 0; i < 10; i++) {
        if (i < 5) {
            mu_assert(ba->data[i] == sa[i], "Wrong character.");
        } else {
            mu_assert(ba->data[i] == sb[i - 5], "Wrong character.");
        }
    }
    return NULL;
}

char *test_biseq() {
    bstring ba = bfromcstr("hello");
    bstring bb = bfromcstr("hello");
    bstring bc = bfromcstr("world");
    mu_assert(biseq(ba, bb) == 1, "Should be equal.");
    mu_assert(biseq(ba, bc) == 0, "Should not be equal.");
    return NULL;
}

char *test_binstr() {
    bstring ba = bfromcstr("hello");
    bstring bb = bfromcstr("lo");
    mu_assert(binstr(ba, 0, bb) == 3, "Should be 3.");
    mu_assert(binstr(ba, 3, bb) == 3, "Should be 3.");
    mu_assert(binstr(ba, 4, bb) == -1, "Should be -1.");
    return NULL;
}

char *test_bfindreplace() {
    bstring ba = bfromcstr("hello");
    bstring bb = bfromcstr("lo");
    bstring bc = bfromcstr("world");
    bstring bd = bfromcstr("helworld");
    bfindreplace(ba, bb, bc, 0);
    for (int i = 0; i < 7; i++) {
        mu_assert(ba->data[i] == bd->data[i], "Wrong character.");
    }
    return NULL;
}

char *test_bsplit() {
    bstring ba = bfromcstr("hello world");
    struct bstrList *bl = bsplit(ba, ' ');
    mu_assert(bl->qty == 2, "Wrong quantity.");
    mu_assert(bl->entry[0]->slen == 5, "Wrong length.");
    mu_assert(bl->entry[1]->slen == 5, "Wrong length.");
    for (int i = 0; i < 5; i++) {
        mu_assert(bl->entry[0]->data[i] == ba->data[i], "Wrong character.");
        mu_assert(bl->entry[1]->data[i] == ba->data[i + 6], "Wrong character.");
    }
    return NULL;
}

char *test_bformat() {
    bstring ba = bformat("%s %s %.2f", "hello", "world", 1.0);
    char *bb = "hello world 1.00";
    mu_assert(ba->slen == strlen(bb), "Wrong length.");
    for (int i = 0; i < ba->slen; i++) {
        mu_assert(ba->data[i] == bb[i], "Wrong character.");
    }
    return NULL;
}

char *test_blength() {
    bstring ba = bfromcstr("hello");
    bstring bb = bfromcstr("");
    mu_assert(blength(ba) == 5, "Wrong length.");
    mu_assert(blength(bb) == 0, "Wrong length.");
    return NULL;
}

char *all_tests() {
    mu_suite_start();
    mu_run_test(test_bfromcstr);
    mu_run_test(test_blk2bstr);
    mu_run_test(test_bstrcpy);
    mu_run_test(test_bassign);
    mu_run_test(test_bassigncstr);
    mu_run_test(test_bassignblk);
    mu_run_test(test_bdestroy);
    mu_run_test(test_bconcat);
    mu_run_test(test_biseq);
    mu_run_test(test_binstr);
    mu_run_test(test_bfindreplace);
    mu_run_test(test_bsplit);
    mu_run_test(test_bformat);
    mu_run_test(test_blength);
    return NULL;
}

RUN_TESTS(all_tests);