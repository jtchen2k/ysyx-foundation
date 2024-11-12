/*
 * ex9.c
 * Project: c
 * Created: 2024-11-11 14:34:03
 * Author: Juntong Chen (dev@jtchen.io)
 * -----
 * Last Modified: 2024-11-11 19:07:05
 * Modified By: Juntong Chen (dev@jtchen.io)
 */
#include <stdio.h>

int main(int argc, char *argv[]) {
    int numbers[4] = {0};
    char name[4] = {'a'};

    // first, print them out raw
    printf("numbers: %d %d %d %d\n",
            numbers[0], numbers[1],
            numbers[2], numbers[3]);

    printf("name each: %c %c %c %c\n",
            name[0], name[1],
            name[2], name[3]);

    printf("name: %s\n", name);

    // setup the numbers
    numbers[0] = 1;
    numbers[1] = 2;
    numbers[2] = 3;
    numbers[3] = 4;

    // setup the name
    name[0] = 'Z';
    name[1] = 'e';
    name[2] = 'd';
    name[3] = '\0';

    // then print them out initialized
    printf("numbers: %d %d %d %d\n",
            numbers[0], numbers[1],
            numbers[2], numbers[3]);

    printf("name each: %c %c %c %c\n",
            name[0], name[1],
            name[2], name[3]);

    // print the name like a string
    printf("name: %s\n", name);

    // another way to use name
    char *another = "Zed";

    printf("another: %s\n", another);

    printf("another each: %c %c %c %c\n",
            another[0], another[1],
            another[2], another[3]);

    unsigned int n = 0;
    char cint[] = {129, 'a', 'g', '\0'};
    for (int i = 0; i < 4; i++) {
        n |= (unsigned int)cint[i] << (i * 8);
    }
    printf("another: %s\n", cint);
    printf("another: %u\n", n);

    return 0;
}
