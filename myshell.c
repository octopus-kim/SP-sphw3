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
#include <sys/wait.h>

void stdout_1 ()
{

}

void stderr_2 () {

}

// > < | & 2> ;
void simple_shell(char **cmd, int count)
{
    int i, j, temp, bg_flag, k = 0;
    int child_pid, status;

    if (strcmp(cmd[count - 1], "&") != 0) bg_flag = 0;
    else { bg_flag = 1; count--; }

    i = 0;
    while (i < count) {
        // Redirection argument : >
        if (strcmp(cmd[i], ">") == 0 || strcmp(cmd[i], "2>") == 0) {
            temp = i - k;
            char *arr[temp + 1];
            arr[temp] = NULL;
            for (j = 0; j < temp; j++) {
                arr[j] = cmd[k]; k++;
            } k = i + 1;

            int out, err;
            out = err = -1;
            while (strcmp(cmd[k], ">") == 0 || strcmp(cmd[k], "2>") == 0 || strcmp(cmd[k], ";") == 0) {
                if (strcmp(cmd[k], ">") == 0)
                    if (k + 1 >= count) {
                        printf("stdout() failed in argument (>)\n"); return;
                    }
                    out = k + 1;
                if (strcmp(cmd[k], "2>") == 0)
                    if (k + 1 >= count) {
                        printf("stdout() failed in argument (>)\n"); return;
                    }
                    err = k + 1;
                if (strcmp(cmd[k], ";") == 0) {
                    i = k; k += 1; break;
                } k += 2;
                if (k >= count) { i = k; break; }
            }

            if ((child_pid = fork()) < 0) {
                printf("fork() failed in argument (>)\n"); return;
            }
            if (child_pid == 0) {
                FILE *fd_out, *fd_err;
                if (out >= 0) {
                    if ((fd_out = fopen(cmd[out], "w")) == NULL) {
                        printf("fopen() failed in argument (>)\n");
                        return;
                    }
                    close(stdout); dup(fd_out); close(fd_out);
                }
                if (err >= 0) {
                    if ((fd_err = fopen(cmd[err], "w")) == NULL) {
                        printf("fopen() failed in argument (>)\n");
                        return;
                    }
                    clode(stderr); dup(fd_err); close(fd_err);
                }

                execvp(arr[0], arr);
                printf("exec() failed in argument (>)\n"); return;
            } else {
                if (bg_flag == 0)
                    waitpid(child_pid, &status, 0);
                else if (bg_flag == 1)
                    waitpid(child_pid, &status, WNOHANG);
            }
        }

        if (strcmp(cmd[i], "2>") == 0) {
            temp = i - k;
            char *arr[temp + 1];
            arr[temp] = NULL;
            for (j = 0; j < temp; j++) {
                arr[j] = cmd[k]; k++;
            } k = i + 1;
        }

        if (strcmp(cmd[i], "<") == 0) {
            temp = i - k;
            char *arr[temp + 1];
            arr[temp] = NULL;
            for (j = 0; j < temp; j++) {
                arr[j] = cmd[k]; k++;
            } k = i + 1;
        }

        if (strcmp(cmd[i], "|") == 0) {
            temp = i - k;
            char *arr[temp + 1];
            arr[temp] = NULL;
            for (j = 0; j < temp; j++) {
                arr[j] = cmd[k]; k++;
            } k = i + 1;
        }

        if (strcmp(cmd[i], ";") == 0) {
            temp = i - k;
            char *arr[temp + 1];
            arr[temp] = NULL;
            for (j = 0; j < temp; j++) {
                arr[j] = cmd[k]; k++;
            } k = i + 1;

            if ((child_pid = fork()) < 0) {
                printf("fork() failed in argument (;)\n"); return;
            }
            if (child_pid == 0) {
                execvp(arr[0], arr);
                printf("exec() failed in argument (;)\n"); return;
            } else {
                if (bg_flag == 0)
                    waitpid(child_pid, &status, 0);
                else if (bg_flag == 1)
                    waitpid(child_pid, &status, WNOHANG);
            }
        }
        i++;
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

            // Count input argument's number
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