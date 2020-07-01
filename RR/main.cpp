#include<iostream>
#include<string>
#include<time.h>
using namespace std;

typedef struct pcb {
	string pName;//进程名
	struct pcb* next;//指向下一个进程
	int arriveTime;//到达时间
	int Runningtime;//运行时间
	char state;//进程的状态
}PCB;

//made by wk 1806100184 cs182 @gzhu

void createProcess(PCB* p, int n) {//创建n个进程，带头结点
	cout << endl << endl << "创建进程" << endl;
	PCB* q = p;//头指针的前一个结点指针
	PCB* r = new PCB;//头指针
	for (int i = 0; i < n; i++) {
		cout << "请输入第" << i + 1 << "个进程的名字:";
		cin >> r->pName;
		//将到达时间和运行时间随机赋予1~5
		r->arriveTime = rand() % 5 + 1;
		r->Runningtime = rand() % 5 + 1;
		//初始状态为就绪状态
		r->state = 'R';
		q->next = r;//将当前r结点接入q->next
		q = r;//将r结点的内容给q结点
		r->next = new PCB;//为r的下一个结点新建一个需要赋值的结点
		r = r->next;//下一个循环是r->next的赋值，r的内容已经给予了当前的q
	}
	//置空便于删除
	r->next = NULL;
	q->next = NULL;
	q = NULL;
	delete q;
	delete r;
	cout << endl << endl;
}

void sortOfArriveTime(PCB* p, int n) {//按到达时间对进程排序
	PCB* t = new PCB;//排序交换的中间传值节点
	PCB* q = new PCB;
	PCB* m = new PCB;
	for (int i = 0; i < n - 1; i++) {//冒泡排序循环
		q = p->next;//q指向链表中的第一个进程
		for (int j = 0; j < n - i - 1; j++) {
			m = q->next;
			if (q->arriveTime > m->arriveTime) {//如果下一个的到达时间小于当前的到达时间结点信息进行交换
				t->pName = q->pName;
				t->arriveTime = q->arriveTime;
				t->Runningtime = q->Runningtime;
				q->pName = m->pName;
				q->arriveTime = m->arriveTime;
				q->Runningtime = m->Runningtime;
				m->pName = t->pName;
				m->arriveTime = t->arriveTime;
				m->Runningtime = t->Runningtime;
			}
			q = q->next;
		}
	}
	t = NULL;
	m = NULL;
	q = NULL;
	delete t;
	delete m;
	delete q;
}

void runProcess(PCB* p, int n) {//运行进程
	PCB* q = new PCB;
	PCB* m = new PCB;
	PCB* s = new PCB;//执行后的就绪队列（存储要运行的进程队列）
	sortOfArriveTime(p, n);//对队列按照到达时间进行排序
	q = p;//指向第一个进程的前一个结点
	m = p->next;//指向第一个进程所在结点
	int currentTime = 0;//当前时间，即时间片
	int i = 0;
	int number = 0;//设立number作为标志记录已经访问过的进程数量
	while (true) {
		currentTime++;//每走一次循环，当前时间+1，即时间片加一，此处可以修改以达到不同时间片的调度情况
		number = 0;
		while (m && m->state == 'C' || m && m->arriveTime > currentTime) {//寻找应该访问的进程
			number++;//每访问一个进程，number+1
			q = m;
			m = m->next;
			if (m == NULL) {//已寻找一遍，重新回到头结点
				q = p;
				m = p->next;
			}
			if (number > n)
				break;
		}
		if (number > n)//每个进程都已过一遍，所有进程都不能进行访问
			continue;
		cout << "正在运行的进程" << endl;
		cout << "当前时间:" << currentTime << endl;
		cout << "进程名\t到达时间  \t运行时间 \t进程状态" << endl;//输出当前正在运行的进程
		cout << m->pName << "\t" << m->arriveTime << "\t  ";
		cout << m->Runningtime << "\t" << m->state << endl;
		m->Runningtime--;
		if (m->Runningtime == 0)//将运行时间为0的进程状态改为‘C’
			m->state = 'C';
		cout << "进程" << m->pName << "执行一次之后就绪队列中的进程" << endl;
		cout << "进程名\t到达时间 还剩运行时间" << endl;
		s = p->next;

		while (s) {//输出就绪队列
			if (s->Runningtime != 0) {
				cout << s->pName << "\t" << s->arriveTime << "\t  ";
				cout << s->Runningtime << "\t" << s->state << endl;
			}
			s = s->next;
		}
		cout << endl << endl << endl;
		q = m;
		m = m->next;//q、m指针后移
		if (m == NULL) {//回到链表头部
			q = p;
			m = p->next;
		}
		s = p->next;
		while (s && s->state == 'C')//若状态为C，则退出队列，下一个进程进行检测
			s = s->next;
		if (s == NULL)//若所有进程已完成，则退出循环
			break;
		i++;
	}
	q = p;
	m = p->next;

	q = NULL;
	m = NULL;
	s = NULL;
	delete q;
	delete m;
	delete s;
	cout << endl;
}

void printProcess(PCB* p) {//输出所有进程的信息
	PCB* q = p->next;
	cout << endl << "当前所有进程信息" << endl;
	cout << "进程名\t到达时间\t状态 " << endl;
	while (q) {
		cout << q->pName << "\t" << q->arriveTime << "\t  " << q->state << endl;
		cout << endl;
		q = q->next;
	}
	cout << endl << endl;
}

int main()
{
	srand((unsigned)time(NULL));
	PCB* p = new PCB;//建立进程块链
	int n;//进程数随机
	n = rand() % 6 + 5;
	cout << "进程个数为:" << n << endl;

	createProcess(p, n);
	printProcess(p);
	runProcess(p, n);
	printProcess(p);
	getchar();
	getchar();
	return 0;
}