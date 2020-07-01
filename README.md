# Round-Robin
时间片轮转调度算法

# 数据结构
typedef struct pcb {
	string pName;//进程名
	struct pcb* next;//指向下一个进程
	int arriveTime;//到达时间
	int Runningtime;//运行时间
	char state;//进程的状态
}PCB;

# 函数
//字如其意
createProcess(p, n);
printProcess(p);
runProcess(p, n);

# 注意事项
如果要在linux下运行，请将头文件<windows.h>替换成<unstid.h>
如果是gcc编译，那么删除windows.h即可，因为标准c中包含了程序中的sleep()函数；如果是g++编译那么便替换成<unstid.h>
并且将Sleep(1000)改为，sleep(1)
