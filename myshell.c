#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>

int main(int argc, char **argv)
{
    int cmd_len, count, child_pid, status;
    int i;
    char *ptr;
    char **cmd;

    if (argc == 1) {
        while(1) {
            printf("$ ");
            scanf("%s", ptr);
            printf("%s\n", ptr);
        }
    }

    else if (argc == 3) {
        if (strcmp(argv[1], "-c") != 0) {
            printf("Usage : %s [-c] [commend] [&]\n", argv[0]); return -1;
        }

        cmd_len = strlen(argv[2]);
        count = 1;
        for (i = 0; i < cmd_len; i++) {
            if (argv[2][i] == ' ') count++;
        }

        cmd = (char**)malloc(sizeof(char*) * count);
        for (i = 0; i < count; i++)
            cmd[i] = (char*)malloc(sizeof(char) * 16);

        i = 0;
        ptr = strtok(argv[2], " ");
        while (ptr != NULL) {
            strcpy(cmd[i], ptr);
            ptr = strtok(NULL, " ");
            i++;
        }

        for (i = 0; i < count; i++)
            printf("%s\n", cmd[i]);
        return 0;
    }

    else {
        printf("Usage : %s [-c] [commend] [&]\n", argv[0]); return -1;
    }


}