#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    while(1) {
        printPrompt();
        char *cmd = get_next_command();

        int child_pid = fork();
        if (child_pid == 0) {
            print("%s, %s, %s\n", cmd[0], cmd[1], cmd[2])
            execlp(cmd[0], cmd[1], cmd[2]);

            panic("exec failed\n")
        } else {
            waitpid(child_pid);
        }
    }
}