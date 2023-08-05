// #include <time.h>

#define MAX_CPU 0.8
#define MAX_MEM 0.8

typedef struct proc
{
    char    USER[30];
    int     PID;
    float  CPU;
    float  MEM;
    int     VSZ;    //占用的虚拟内存大小
    int     RSS;    //占用内存大小
    char    TTY[20];
    char    STAT[20];
    char      START[20];
    char     TIME[20];
}proc;

int get_proc_info(char*, proc*);
int check_proc(proc*);
