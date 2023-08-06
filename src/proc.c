#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "include/proc.h"
#include "include/ps.h"
#include "include/mail.h"


char proc_list[66000];  //记录进程号


int get_proc_info(char* buffer, proc* temp_proc){
    char* delim = " ";
    char temp[1024];
    int pid;
    strcpy(temp, buffer);
        char *p = strtok(temp, delim);
        enum attribute i = 0;
        while (p)
        {
            switch (i)
            {
            case USER:
                strcpy(temp_proc->USER, p);
                break;

            case PID:
                pid = atoi(p);
                temp_proc->PID = pid;
                proc_list[pid] = 1;
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
        // printf("%s,%d,%f,%f,%d,%d,%s,%s,%s,%s\n", temp_proc->USER, temp_proc->PID, temp_proc->CPU, temp_proc->MEM, temp_proc->VSZ, temp_proc->RSS, temp_proc->TTY, temp_proc->STAT, temp_proc->START, temp_proc->TIME);
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

int get_all_proc_info(void){
    FILE *fp;
    char buffer[1024];
    char* delim = " ";
    char temp[1024];
    int flag = 0;   //judge whether it's the first line
    memset(proc_list, 0, sizeof(proc_list));
    fp = popen("sudo ps -aux", "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        return 1;
    }
    
    while (fgets(buffer, sizeof(buffer)-1, fp) != NULL) {
        // printf("%s", buffer);
        if (!flag)
        {
            flag = 1;
            continue;
        }
        proc p;
        get_proc_info(buffer, &p);  
        check_proc(&p);
    }

    pclose(fp);
}