#include <time.h>

typedef struct
{
    char    USER[20];
    int     PID;
    double  CPU;
    double  MEM;
    int     VSZ;
    int     RSS;
    char    STAT[20];
    tm      START;
    tm      TIME;
}proc;
