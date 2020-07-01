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
