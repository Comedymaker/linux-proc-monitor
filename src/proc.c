#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "include/proc.h"
#include "include/ps.h"
#include "include/mail.h"


int get_proc_info(char* buffer, proc* temp_proc){
    char* delim = " ";
    char temp[1024];

    strcpy(temp, buffer);
        char *p = strtok(buffer, delim);
        enum attribute i = 0;
        while (p)
        {
            switch (i)
            {
            case USER:
                strcpy(temp_proc->USER, p);
                break;

            case PID:
                temp_proc->PID = atoi(p);
                break;

            case CPU:
                temp_proc->CPU = atof(p);
                break;

            case MEM:
                temp_proc->MEM = atof(p);
                break;

            case VSZ:
                temp_proc->VSZ = atoi(p);
                break;

            case RSS:
                temp_proc->RSS = atoi(p);
                break;
            
            case TTY:
                strcpy(temp_proc->TTY, p);
                break;

            case STAT:
                strcpy(temp_proc->STAT, p);
                break;

            case START:
                strcpy(temp_proc->START, p);
                break;

            case TIME:
                strcpy(temp_proc->TIME, p);
                break;
            
            default:
                break;
            }
            i++;
            p = strtok(NULL, delim);
        }
        printf("%s,%d,%f,%f,%d,%d,%s,%s,%s,%s\n", temp_proc->USER, temp_proc->PID, temp_proc->CPU, temp_proc->MEM, temp_proc->VSZ, temp_proc->RSS, temp_proc->TTY, temp_proc->STAT, temp_proc->START, temp_proc->TIME);
        return 0;
}

int check_proc(proc* p){
    if (p->CPU > MAX_CPU)
    {
        send_mail(p->PID, "CPU usage for too much!");
        return -1;
    }
    if (p->MEM > MAX_MEM)
    {
        send_mail(p->PID, "MEM usage for too much!");
        return -1;
    }
    return 0;
}