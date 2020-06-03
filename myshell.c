#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int i = 0;
    // myshell -c [arg] [arg] ...
    if (argc > 1) {
        // check argument
        if (argv[1] != "-c") {
            printf("Usage : %s -c [arg] [arg] ...\n", argv[0]);
            for (i = 0; i < argc; i++)
                printf("%s\n", argv[i]);
            return -1;
        }
        printf("%d arg\n", argc - 1);
    }

    // myshell
    else {
        printf("0 arg\n");
    }
}