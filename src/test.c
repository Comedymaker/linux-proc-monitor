#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "include/proc.h"
#include "include/ps.h"
#include "include/mail.h"
#include "include/network.h"
#include "sys/inotify.h"

#define EVENT_SIZE  (sizeof (struct inotify_event))
#define BUF_SIZE    (1024 * (EVENT_SIZE + 16))
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
    //     proc p;
    //     get_proc_info(buffer, &p);  
    //     check_proc(&p);
    //     proc_num++;
    // }

    // pclose(fp);
    // get_all_proc_info();
    // check_invisible_proc();
    // set_proc_net_monitor(4988);
int fd, wd;
    char buffer[BUF_SIZE];

    // 创建inotify实例
    fd = inotify_init();
    if (fd < 0) {
        perror("inotify_init");
        return 1;
    }

    // 添加需要监视的目录
    wd = inotify_add_watch(fd, "/home/comedymaker/tmp", IN_MODIFY | IN_CREATE | IN_DELETE);
    if (wd < 0) {
        perror("inotify_add_watch");
        return 1;
    }

    // 开始监视
    printf("Monitoring directory: %s\n", "/home/comedymaker/tmp");
    while (1) {
        int length, i = 0;
        length = read(fd, buffer, BUF_SIZE);
        if (length < 0) {
            perror("read");
            return 1;
        }

        while (i < length) {
            struct inotify_event *event = (struct inotify_event *)&buffer[i];
            if (event->mask & IN_MODIFY)
                printf("File modified: %s\n", event->name);
            if (event->mask & IN_CREATE)
                printf("File created: %s\n", event->name);
            if (event->mask & IN_DELETE)
                printf("File deleted: %s\n", event->name);
            i += EVENT_SIZE + event->len;
        }
    }

    // 终止监视
    inotify_rm_watch(fd, wd);
    close(fd);

    return 0;
}
