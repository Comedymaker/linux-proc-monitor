#include "sys/inotify.h"

#define EVENT_SIZE  (sizeof (struct inotify_event))
#define BUF_SIZE    (1024 * (EVENT_SIZE + 16))

int set_file_monitor(char* path);