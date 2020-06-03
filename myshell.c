#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    // myshell -c [arg] [arg] ...
    if (argc > 1) {
        // check argument
        if (strcmp(argv[1], "-c") != 0) {
            printf("Usage : %s -c [arg] [arg] ...\n", argv[0]); return -1;
        }
        printf("%d arg\n", argc - 1);
    }

    // myshell
    else {
        printf("0 arg\n");
    }

    return 0;
}