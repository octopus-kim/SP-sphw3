#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    while(1) {
        int i = 0;
        char **cmd;
        printf("$ ");

        for (i = 0; i < argc; i++) {
            cmd[i] = argv[i]
        }

        int child_pid = fork();
        if (child_pid == 0) {
            execlp(cmd[0], cmd[0], cmd[1], cmd[2]);
            printf("exec failed\n");
        } else {
            waitpid(child_pid);
        }
    }
}