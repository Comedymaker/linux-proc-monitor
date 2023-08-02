#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    char buffer[1024];

    fp = popen("ps -au", "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        return 1;
    }
    char* delim = " ";
    char temp[1024];

    while (fgets(buffer, sizeof(buffer)-1, fp) != NULL) {
        // printf("%s", buffer);
        strcpy(temp, buffer);
        char *p = strtok(buffer, delim);
        while (p)
        {
            printf("%s\n", p);
            p = strtok(NULL, delim);
        }
        memset(temp, 0, sizeof(temp));
    }

    pclose(fp);
    return 0;
}
