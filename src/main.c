#include <stdio.h>
#include <stdlib.h>
#include <include/proc.h>

int main() {
    FILE *fp;
    char buffer[1024];

    fp = popen("ps -aux", "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        return 1;
    }

    while (fgets(buffer, sizeof(buffer)-1, fp) != NULL) {
        printf("%s", buffer);
    }

    pclose(fp);
    return 0;
}