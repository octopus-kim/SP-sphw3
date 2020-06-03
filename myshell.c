#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    while(1) {
        printf("$ ");

        int child_pid = fork();
        if (child_pid == 0) {
            execlp(argv[0], argv[0], argv[1], argv[2]);
            printf("exec failed\n");
        } else {
            waitpid(child_pid);
        }
    }
}