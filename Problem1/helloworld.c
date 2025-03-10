/*
 * Program: Hello World Printer
 * Description: This program prints "Hello World!" a specified number of times.
 * Command Line Arguments: 
 *     - An integer specifying how many times to print "Hello World!"
 * Example Invocation:
 *     ./helloworld 3
 * Output:
 *     Hello World!
 *     Hello World!
 *     Hello World!
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]); // Convert argument to integer
    for (int i = 0; i < n; i++) {
        printf("Hello World!\n");
    }
    return 0;
}

