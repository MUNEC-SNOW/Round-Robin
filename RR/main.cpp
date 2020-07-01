#include<iostream>
#include<string>
#include<time.h>
using namespace std;

typedef struct pcb {
	string pName;//������
	struct pcb* next;//ָ����һ������
	int arriveTime;//����ʱ��
	int Runningtime;//����ʱ��
	char state;//���̵�״̬
}PCB;

//made by wk 1806100184 cs182 @gzhu

void createProcess(PCB* p, int n) {//����n�����̣���ͷ���
	cout << endl << endl << "��������" << endl;
	PCB* q = p;//ͷָ���ǰһ�����ָ��
	PCB* r = new PCB;//ͷָ��
	for (int i = 0; i < n; i++) {
		cout << "�������" << i + 1 << "�����̵�����:";
		cin >> r->pName;
		//������ʱ�������ʱ���������1~5
		r->arriveTime = rand() % 5 + 1;
		r->Runningtime = rand() % 5 + 1;
		//��ʼ״̬Ϊ����״̬
		r->state = 'R';
		q->next = r;//����ǰr������q->next
		q = r;//��r�������ݸ�q���
		r->next = new PCB;//Ϊr����һ������½�һ����Ҫ��ֵ�Ľ��
		r = r->next;//��һ��ѭ����r->next�ĸ�ֵ��r�������Ѿ������˵�ǰ��q
	}
	//�ÿձ���ɾ��
	r->next = NULL;
	q->next = NULL;
	q = NULL;
	delete q;
	delete r;
	cout << endl << endl;
}

void sortOfArriveTime(PCB* p, int n) {//������ʱ��Խ�������
	PCB* t = new PCB;//���򽻻����м䴫ֵ�ڵ�
	PCB* q = new PCB;
	PCB* m = new PCB;
	for (int i = 0; i < n - 1; i++) {//ð������ѭ��
		q = p->next;//qָ�������еĵ�һ������
		for (int j = 0; j < n - i - 1; j++) {
			m = q->next;
			if (q->arriveTime > m->arriveTime) {//�����һ���ĵ���ʱ��С�ڵ�ǰ�ĵ���ʱ������Ϣ���н���
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

void runProcess(PCB* p, int n) {//���н���
	PCB* q = new PCB;
	PCB* m = new PCB;
	PCB* s = new PCB;//ִ�к�ľ������У��洢Ҫ���еĽ��̶��У�
	sortOfArriveTime(p, n);//�Զ��а��յ���ʱ���������
	q = p;//ָ���һ�����̵�ǰһ�����
	m = p->next;//ָ���һ���������ڽ��
	int currentTime = 0;//��ǰʱ�䣬��ʱ��Ƭ
	int i = 0;
	int number = 0;//����number��Ϊ��־��¼�Ѿ����ʹ��Ľ�������
	while (true) {
		currentTime++;//ÿ��һ��ѭ������ǰʱ��+1����ʱ��Ƭ��һ���˴������޸��Դﵽ��ͬʱ��Ƭ�ĵ������
		number = 0;
		while (m && m->state == 'C' || m && m->arriveTime > currentTime) {//Ѱ��Ӧ�÷��ʵĽ���
			number++;//ÿ����һ�����̣�number+1
			q = m;
			m = m->next;
			if (m == NULL) {//��Ѱ��һ�飬���»ص�ͷ���
				q = p;
				m = p->next;
			}
			if (number > n)
				break;
		}
		if (number > n)//ÿ�����̶��ѹ�һ�飬���н��̶����ܽ��з���
			continue;
		cout << "�������еĽ���" << endl;
		cout << "��ǰʱ��:" << currentTime << endl;
		cout << "������\t����ʱ��  \t����ʱ�� \t����״̬" << endl;//�����ǰ�������еĽ���
		cout << m->pName << "\t" << m->arriveTime << "\t  ";
		cout << m->Runningtime << "\t" << m->state << endl;
		m->Runningtime--;
		if (m->Runningtime == 0)//������ʱ��Ϊ0�Ľ���״̬��Ϊ��C��
			m->state = 'C';
		cout << "����" << m->pName << "ִ��һ��֮����������еĽ���" << endl;
		cout << "������\t����ʱ�� ��ʣ����ʱ��" << endl;
		s = p->next;

		while (s) {//�����������
			if (s->Runningtime != 0) {
				cout << s->pName << "\t" << s->arriveTime << "\t  ";
				cout << s->Runningtime << "\t" << s->state << endl;
			}
			s = s->next;
		}
		cout << endl << endl << endl;
		q = m;
		m = m->next;//q��mָ�����
		if (m == NULL) {//�ص�����ͷ��
			q = p;
			m = p->next;
		}
		s = p->next;
		while (s && s->state == 'C')//��״̬ΪC�����˳����У���һ�����̽��м��
			s = s->next;
		if (s == NULL)//�����н�������ɣ����˳�ѭ��
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

void printProcess(PCB* p) {//������н��̵���Ϣ
	PCB* q = p->next;
	cout << endl << "��ǰ���н�����Ϣ" << endl;
	cout << "������\t����ʱ��\t״̬ " << endl;
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
	PCB* p = new PCB;//�������̿���
	int n;//���������
	n = rand() % 6 + 5;
	cout << "���̸���Ϊ:" << n << endl;

	createProcess(p, n);
	printProcess(p);
	runProcess(p, n);
	printProcess(p);
	getchar();
	getchar();
	return 0;
}