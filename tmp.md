## 临时记录

##### 网络相关

使用netstat -p | grep ****指令监控指定进程网络状态，定时轮询，返回使用端口及其状态，一旦断开则mail管理员

##### 找到进程隐藏

+ 查看/proc/mount，一旦出现则mail管理员
+ 将现在test中的内容封装成一个函数check_all_proc，并将当前已有的进程存到数组中；查看netstat -p，如果出现没有的进程，则说明是隐藏进程，一旦出现则mail管理员

##### 目录监控

使用sys/inotify.h库

##### 最终整合

完成所有功能以后，需要构造一个交互式界面“如果有条件尽量符合开源的命令行项目的UI”
