/*
 * ex10.c
 * Project: c
 * Created: 2024-11-11 14:49:29
 * Author: Juntong Chen (dev@jtchen.io)
 * -----
 * Last Modified: 2024-11-11 19:07:05
 * Modified By: Juntong Chen (dev@jtchen.io)
 */
#include <stdio.h>

int main(int argc, char *argv[])
{
    int i = 0;

    // go through each string in argv
    // why am I skipping argv[0]?
    for(i = 1; i < argc; i++) {
        printf("arg %d: %s\n", i, argv[i]);
    }

    // let's make our own array of strings
    char *states[] = {
        "California", "Oregon",
        "Washington", "Texas"
    };
    int num_states = 4;

    for(i = 0; i < num_states; i++) {
        printf("state %d: %s\n", i, states[i]);
    }

    char str[5][6] = {"abcde", "fghij", "klmno", "pqrst", "uvwxy"};

    printf("Size of states: %ld\n", sizeof(str[0]));

    return 0;
}