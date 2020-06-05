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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void stdout_1 ()
{

}

void stderr_2 () {

}

// > < | & 2> ;
int simple_shell(char **cmd, int count)
{
    int i, j, temp, out, err, k = 0;
    int child_pid, status, fd_in, fd_out, fd_err;
    int bg_flag, arg_flag;

    if (strcmp(cmd[count - 1], "&") != 0) bg_flag = 0;
    else { bg_flag = 1; count--; }

    arg_flag = i = 0;
    while (i < count) {
        // Redirection argument : >
        if (strcmp(cmd[i], ">") == 0 || strcmp(cmd[i], "2>") == 0) {
            arg_flag = 1;
            temp = i - k;
            char *arr[temp + 1];
            arr[temp] = NULL;
            for (j = 0; j < temp; j++) {
                arr[j] = cmd[k]; k++;
            }

            out = err = -1;
            for ( k = i; k < count; k += 2) {
                if (strcmp(cmd[k], ">") == 0) {
                    if ((k + 1) >= count) {
                        fprintf(stderr, "stdout failed in argument (>)\n"); return -1;
                    } out = k + 1;
                    if ((fd_out = open(cmd[out], O_WRONLY | O_CREAT, 0600)) < 0) {
                        fprintf(stderr, "dummy open() failed in argument (>)\n"); return -1;
                    } close(fd_out);
                }
                else if (strcmp(cmd[k], "2>") == 0) {
                    if ((k + 1) >= count) {
                        fprintf(stderr, "stderr failed in argument (2>)\n"); return -1;
                    } err = k + 1;
                    if ((fd_err = open(cmd[err], O_WRONLY | O_CREAT, 0600)) < 0) {
                        fprintf(stderr, "dummy open() failed in argument (2>)\n"); return -1;
                    } close(fd_err);
                }
                else if (strcmp(cmd[k], ";") == 0) {
                    k += 1; break;
                }
                else {
                    fprintf(stderr, "invalid argument is detected in argument (> or 2>)\n"); return -1;
                }
            } i = k - 1;

            if ((child_pid = fork()) < 0) {
                fprintf(stderr, "fork() failed in argument (> or 2>)\n"); return -1;
            }
            if (child_pid == 0) {
                if (out >= 0) {
                    if ((fd_out = open(cmd[out], O_WRONLY | O_CREAT, 0600)) < 0) {
                        fprintf(stderr, "open() failed in argument (>)\n"); return -1;
                    }
                    close(1); dup(fd_out); close(fd_out);
                }
                if (err >= 0) {
                    if ((fd_err = open(cmd[err], O_WRONLY | O_CREAT, 0600)) < 0) {
                        fprintf(stderr, "open() failed in argument (2>)\n"); return -1;
                    }
                    close(2); dup(fd_err); close(fd_err);
                }

                execvp(arr[0], arr);
                fprintf(stderr, "exec() failed in argument (> or 2>)\n"); return -1;
            } else {
                if (bg_flag == 0)
                    waitpid(child_pid, &status, 0);
                else if (bg_flag == 1)
                    waitpid(child_pid, &status, WNOHANG);
            }
        }

        else if (strcmp(cmd[i], "<") == 0) {
            arg_flag = 1;
            temp = i - k;
            char *arr[temp + 1];
            arr[temp] = NULL;
            for (j = 0; j < temp; j++) {
                arr[j] = cmd[k]; k++;
            }

            if ((fd_in = open(cmd[i + 1], O_RDONLY)) < 0) {
                fprintf(stderr, "open() failed in argument (<)\n"); return -1;
            }

            out = err = -1;
            for ( k = i; k < count; k += 2) {
                if (strcmp(cmd[k], "<") == 0) continue;
                else if (strcmp(cmd[k], "|") == 0) {
                    return -1;
                }
                else if (strcmp(cmd[k], ">") == 0) {
                    if ((k + 1) >= count) {
                        fprintf(stderr, "stdout failed in argument (<)\n"); return -1;
                    } out = k + 1;
                    if ((fd_out = open(cmd[out], O_WRONLY | O_CREAT, 0600)) < 0) {
                        fprintf(stderr, "dummy open() failed in argument (<)\n"); return -1;
                    } close(fd_out);
                }
                else if (strcmp(cmd[k], "2>") == 0) {
                    if ((k + 1) >= count) {
                        fprintf(stderr, "stderr failed in argument (<)\n"); return -1;
                    } err = k + 1;
                    if ((fd_err = open(cmd[err], O_WRONLY | O_CREAT, 0600)) < 0) {
                        fprintf(stderr, "dummy open() failed in argument (<)\n"); return -1;
                    } close(fd_err);
                }
                else if (strcmp(cmd[k], ";") == 0) {
                    k += 1; break;
                }
                else {
                    fprintf(stderr, "invalid argument is detected in argument (<)\n"); return -1;
                }
            } i = k - 1;

            if ((child_pid = fork()) < 0) {
                fprintf(stderr, "fork() failed in argument (<)\n"); return -1;
            }
            if (child_pid == 0) {
                if (out >= 0) {
                    if ((fd_out = open(cmd[out], O_WRONLY | O_CREAT, 0600)) < 0) {
                        fprintf(stderr, "open() failed in argument (<)\n"); return -1;
                    }
                    close(1); dup(fd_out); close(fd_out);
                }
                if (err >= 0) {
                    if ((fd_err = open(cmd[err], O_WRONLY | O_CREAT, 0600)) < 0) {
                        fprintf(stderr, "open() failed in argument (<)\n"); return -1;
                    }
                    close(2); dup(fd_err); close(fd_err);
                }
                close(0); dup(fd_in); close(fd_in);

                execvp(arr[0], arr);
                fprintf(stderr, "exec() failed in argument (<)\n"); return -1;
            } else {
                if (bg_flag == 0)
                    waitpid(child_pid, &status, 0);
                else if (bg_flag == 1)
                    waitpid(child_pid, &status, WNOHANG);
            }
        }

        else if (strcmp(cmd[i], "|") == 0) {
            arg_flag = 1;
            temp = i - k;
            char *arr[temp + 1];
            arr[temp] = NULL;
            for (j = 0; j < temp; j++) {
                arr[j] = cmd[k]; k++;
            } k = i + 1;
        }

        else if (strcmp(cmd[i], ";") == 0) {
            arg_flag = 1;
            temp = i - k;
            char *arr[temp + 1];
            arr[temp] = NULL;
            for (j = 0; j < temp; j++) {
                arr[j] = cmd[k]; k++;
            } k = i + 1;

            if ((child_pid = fork()) < 0) {
                fprintf(stderr, "fork() failed in argument (;)\n"); return -1;
            }
            if (child_pid == 0) {
                execvp(arr[0], arr);
                fprintf(stderr, "exec() failed in argument (;)\n"); return -1;
            } else {
                if (bg_flag == 0)
                    waitpid(child_pid, &status, 0);
                else if (bg_flag == 1)
                    waitpid(child_pid, &status, WNOHANG);
            }
        }
        i++;
    }

    if (arg_flag == 0) {
        char *arr[count + 1];
        arr[count] = NULL;
        for (i = 0; i < count; i++) {
            arr[i] = cmd[i];
        }

        if ((child_pid = fork()) < 0) {
            fprintf(stderr, "fork() failed in argument (none)\n"); return -1;
        }
        if (child_pid == 0) {
            execvp(arr[0], arr);
            fprintf(stderr, "exec() failed in argument (none)\n"); return -1;
        } else {
            if (bg_flag == 0)
                waitpid(child_pid, &status, 0);
            else if (bg_flag == 1)
                waitpid(child_pid, &status, WNOHANG);
        }
    } return 0;
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

            if (simple_shell(cmd, count) < 0) {
                return -1;
            }
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

        if (simple_shell(cmd, count) < 0) {
            return -1;
        }
        return 0;
    }

    else {
        printf("Usage : %s [-c] [commend] [&]\n", argv[0]); return -1;
    }
}