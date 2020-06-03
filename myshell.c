#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    int cmd_len, count;
    int temp, i, j;
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
            if (strcmp(argv[2][i], " ") == 0) count++;
        }

        cmd = (char**)malloc(sizeof(char*) * count);
        for (i = 0; i < count; i++)
            cmd[i] = (char*)malloc(sizeof(char) * 10);

        temp = 0; j = 0;
        for (i = 0; i < cmd_len; i++) {
            if (strcmp(argv[2][i], " ") != 0) {
                j++; temp = 0; continue;
            }
            cmd[j][temp] = argv[2][i];
            temp++;
        }

        for (i = 0; i < count; i++)
            printf("%s\n", cmd[i]);
    } else {
        printf("Usage : %s [-c] [commend]\n", argv[0]); return -1;
    }

    return 0;
}