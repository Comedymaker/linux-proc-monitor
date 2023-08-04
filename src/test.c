#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "include/proc.h"
#include "include/ps.h"

proc proc_list[1000];
int proc_num = 0;

int main() {
    // FILE *fp;
    // char buffer[1024];
    // char* delim = " ";
    // char temp[1024];
    // int flag = 0;   //judge whether it's the first line

    // fp = popen("ps -au", "r");
    // if (fp == NULL) {
    //     printf("Failed to run command\n");
    //     return 1;
    // }
    
    // while (fgets(buffer, sizeof(buffer)-1, fp) != NULL) {
    //     // printf("%s", buffer);
    //     if (!flag)
    //     {
    //         flag = 1;
    //         continue;
    //     }
    //     get_proc_info(buffer);  
    //     proc_num++;
    // }

    // pclose(fp);
    char *cmd[200];
    sprintf(cmd, "echo \"Subject: error proc!\r\n\r\ntarget proc: %d\" | sendmail -t 544738192@qq.com", 100);
    system(cmd);
    return 0;
}
