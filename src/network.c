#include "include/network.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "unistd.h"

//only for tcp
int check_proc_netstat(int proc_num){
    int ret = -1;
    char cmd[200];
    sprintf(cmd, "netstat -p | grep %d", proc_num);
    FILE *fp;
    char buffer[1024];
    char* delim = " ";

    fp = popen(cmd, "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        return 1;
    }

    proc_net p_net;

    while (fgets(buffer, sizeof(buffer)-1, fp) != NULL) {
        // printf("%s", buffer);
        enum net_attribute i = 0;
        
        char temp[1024];
        strcpy(temp, buffer);
        char pid_pname[100];
        int j;
        char *p = strtok(temp, delim);

        while (p)
        {
            switch (i)
            {
            case PROTO:
                strcpy(p_net.proto, p);
                break;

            case RECV_Q:
                p_net.recv = atoi(p);
                break;

            case SEND_Q:
                p_net.send = atoi(p);
                break;

            case LOCAL_ADDR:
                strcpy(p_net.local_addr, p);
                break;

            case FOREIGN_ADDR:
                strcpy(p_net.foreign_addr, p);
                break;

            case STATE:
                strcpy(p_net.state, p);
                break;

            case PID_PNAME:
                strcpy(pid_pname, p);
                for (j = 0; pid_pname[j] >= '0' && pid_pname[j] <= '9'; j++)
                {

                }
                pid_pname[j] = 0;
                if (j > 0)
                {
                    p_net.pid = atoi(pid_pname);   
                }
                else
                    p_net.pid = 0;   
                break;
            
            default:
                break;
            }
            i++;
            p = strtok(NULL, delim);
        }

        if (strcmp(p_net.state, "ESTABLISHED") == 0)
        {
            printf("CONNECTED OK!\n");
            ret = 1;
        }
        else
        {
            ret = 0;
        }
                  
        // printf("%s, %d, %d, %s, %s, %s, %d\n", p_net.proto, p_net.recv, p_net.send, p_net.local_addr, p_net.foreign_addr, p_net.state, p_net.pid);
    }
    pclose(fp);
    return ret;
}

int set_proc_net_monitor(int proc_num)
{
    while (1)
    {
        if (check_proc_netstat(proc_num) != 1)
        {
            printf("proc connect error!\n");
            return 0;
        }
        printf("arrive here!\n");
        sleep(1);
    }
    return 0;
}