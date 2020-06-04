/*
 * Year     : 2020
 * Subject  : SystemProgramming
 * Homework : Simple shell program
 * StudentID: B511032
 * Name     : SungJo Kim
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>

// > < | & 2> ;
void simple_shell(char **cmd, int count)
{
    int i, j, k = 0;

    for (i = 0; i < count; i++) {
        if (strcmp(cmd[i], ">") == 0) {
            const char *arr[i - k + 1];
            arr[i - k] = NULL;
            for (j = 0; j < i - k; j++) {
                arr[j] = cmd[k];
                printf("arr[%d] -> %s\n", j, arr[j]);
                k++;
            }
            k = i + 1;
        }
        if (strcmp(cmd[i], "<") == 0) {
            const char *arr[i - k + 1];
            arr[i - k] = NULL;
            for (j = 0; j < i - k; j++) {
                arr[j] = cmd[k];
                printf("arr[%d] -> %s\n", j, arr[j]);
                k++;
            }
            k = i + 1;
        }
        if (strcmp(cmd[i], "2>") == 0) {
            const char *arr[i - k + 1];
            arr[i - k] = NULL;
            for (j = 0; j < i - k; j++) {
                arr[j] = cmd[k];
                printf("arr[%d] -> %s\n", j, arr[j]);
                k++;
            }
            k = i + 1;
        }
        if (strcmp(cmd[i], "|") == 0) {
            const char *arr[i - k + 1];
            arr[i - k] = NULL;
            for (j = 0; j < i - k; j++) {
                arr[j] = cmd[k];
                printf("arr[%d] -> %s\n", j, arr[j]);
                k++;
            }
            k = i + 1;
        }
        if (strcmp(cmd[i], "&") == 0) {
            const char *arr[i - k + 1];
            arr[i - k] = NULL;
            for (j = 0; j < i - k; j++) {
                arr[j] = cmd[k];
                printf("arr[%d] -> %s\n", j, arr[j]);
                k++;
            }
            k = i + 1;
        }
        if (strcmp(cmd[i], ";") == 0) {
            const char *arr[i - k + 1];
            arr[i - k] = NULL;
            for (j = 0; j < i - k; j++) {
                arr[j] = cmd[k];
                printf("arr[%d] -> %s\n", j, arr[j]);
                k++;
            }
            k = i + 1;
        }
    }
}

int main(int argc, char *argv[])
{
    int cmd_len, count, child_pid, status, i;
    int MAXSIZE = 64;
    char s_ptr[MAXSIZE];
    char *d_ptr;
    char **cmd;

    if (argc == 1) {
        while(1) {
            // Block process until an I/O event occurs
            printf("$ ");
            fgets(s_ptr, MAXSIZE, stdin);

            // If EOF event occurs, then exit process normally
            if (feof(stdin)) {
                printf("CTRL + D\nexit program normally\n"); return 0;
            }

            // Count argument's number
            cmd_len = strlen(s_ptr);
            count = 1;
            for (i = 0; i < cmd_len; i++) {
                if (s_ptr[i] == ' ') count++;
            }

            // Dynamic allocation of cmd array for saving arguments
            cmd = (char**)malloc(sizeof(char*) * count);
            for (i = 0; i < count; i++)
                cmd[i] = (char*)malloc(sizeof(char) * MAXSIZE);

            // Save arguments in cmd array
            i = 0;
            d_ptr = strtok(s_ptr, " ");
            while (d_ptr != NULL) {
                strcpy(cmd[i], d_ptr);
                d_ptr = strtok(NULL, " ");
                i++;
            } i = 0;
            while (cmd[count - 1][i] != '\n') i++;
            cmd[count - 1][i] = '\0';

            simple_shell(cmd, count);
        }
    }

    else if (argc == 3) {
        // IF 2rd argument is not "-c", then exit program abnormally with error msg
        if (strcmp(argv[1], "-c") != 0) {
            printf("Usage : %s [-c] [commend] [&]\n", argv[0]); return -1;
        }

        // Count argument's number
        cmd_len = strlen(argv[2]);
        count = 1;
        for (i = 0; i < cmd_len; i++) {
            if (argv[2][i] == ' ') count++;
        }

        // Dynamic allocation of cmd array for saving arguments
        cmd = (char**)malloc(sizeof(char*) * count);
        for (i = 0; i < count; i++)
            cmd[i] = (char*)malloc(sizeof(char) * MAXSIZE);

        // Save arguments in cmd array
        i = 0;
        d_ptr = strtok(argv[2], " ");
        while (d_ptr != NULL) {
            strcpy(cmd[i], d_ptr);
            d_ptr = strtok(NULL, " ");
            i++;
        }

        simple_shell(cmd, count);
        return 0;
    }

    else {
        printf("Usage : %s [-c] [commend] [&]\n", argv[0]); return -1;
    }
}