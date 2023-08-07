#include "stdio.h"
#include "stdlib.h"
#include "include/inoty.h"

int set_file_monitor(char* path)
{
    int fd, wd;
    char buffer[BUF_SIZE];
    fd = inotify_init();

    if (fd < 0)
    {
        printf("inotify init error!\n");
        return -1;
    }
    
    wd = inotify_add_watch(fd, path, IN_MODIFY | IN_CREATE | IN_DELETE);
    if (wd < 0)
    {
        printf("inotify add watch error!\n");
        return -1;
    }
    
    printf("Begin to monitor directory: %s\n", path);
    while (1) {
        int length, i = 0;
        length = read(fd, buffer, BUF_SIZE);
        if (length < 0) {
            printf("read file error!\n");
            return -1;
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

    inotify_rm_watch(fd, wd);
    close(fd);

    return 0;
}