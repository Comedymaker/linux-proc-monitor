enum net_attribute { PROTO, RECV_Q, SEND_Q, LOCAL_ADDR, FOREIGN_ADDR, STATE, PID_PNAME };

typedef struct proc_net
{
    char proto[20];
    int recv;
    int send;
    char local_addr[50];
    char foreign_addr[50];
    char state[20];
    int pid;
}proc_net;


int check_proc_netstat(int proc_num);
int set_proc_net_monitor(int proc_num);