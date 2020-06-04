#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>

int main(int argc, char **argv)
{
    int bg_flag, cmd_len, count, child_pid, status;
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

        if (strcmp(cmd[count - 1], "&") == 0) bg_flag = 1;
        else bg_flag = 0;

        child_pid = fork();
        if (child_pid == 0) {
            execlp(cmd[0], cmd[0], cmd[1], 0);
        } else {
            if (bg_flag == 0) {
                waitpid(child_pid, &status, 0);
            } else if (bg_flag == 1) {
                waitpid(child_pid, &status, WNOHANG);
                return 0;
            }
        }
    }

    else {
        printf("Usage : %s [-c] [commend] [&]\n", argv[0]); return -1;
    }

    return 0;
}