#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    int cmd_len, count;
    int temp, i, j;
    char *ptr;
    char **cmd;
    if (argc == 1) {

    }
    else if (argc == 3) {
        if (strcmp(argv[1], "-c") != 0) {
            printf("Usage : %s [-c] [commend]\n", argv[0]); return -1;
        }

        cmd_len = strlen(argv[2]);
        count = 1;
        for (i = 0; i < cmd_len; i++) {
            if (strncmp(argv[2], " ", 1) == 0) count++;
        }

        i = 0;
        cmd = (char**)malloc(sizeof(char*) * count);
        for (i = 0; i < count; i++)
            cmd[i] = (char*)malloc(sizeof(char) * 16);
        ptr = strtok(argv[2], " ");
        while (ptr != NULL) {
            printf("%s\n", ptr);
            strcpy(cmd[i], ptr);
            ptr = strtok(NULL, " ");
        }

        for (i = 0; i < count; i++)
            printf("%s\n", cmd[i]);
    } else {
        printf("Usage : %s [-c] [commend]\n", argv[0]); return -1;
    }

    return 0;
}