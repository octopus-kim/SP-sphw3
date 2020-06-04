#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>

int main(int argc, char **argv)
{
    int cmd_len, count, child_pid, status;
    int i;
    char s_ptr[16];
    char *d_ptr;
    char **cmd;

    if (argc == 1) {
        while(1) {
            printf("$ ");
            scanf("%s", s_ptr);
            printf("%s\n", s_ptr);
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
        d_ptr = strtok(argv[2], " ");
        while (d_ptr != NULL) {
            strcpy(cmd[i], d_ptr);
            d_ptr = strtok(NULL, " ");
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