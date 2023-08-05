#include "stdio.h"
#include "stdlib.h"
int send_mail(int proc_uid, char* content){
    char cmd[200];
    sprintf(cmd, "echo \"Subject: error proc %d!\r\n\r\n%s\" | sendmail -t 544738192@qq.com", proc_uid,content);
    system(cmd);
    return 0;
}