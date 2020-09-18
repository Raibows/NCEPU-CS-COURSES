// ConsoleApplication10.cpp: �������̨Ӧ�ó������ڵ㡣
//#include "stdafx.h"
#include<iostream>
#include<string>
using namespace std;
const float fee = 10;  //10 yuan per minute
const int all = 2;   //parkinglot max is 2
class node {
public:
	node(string x);
	~node();
	string license;
	node *next;
};
node::~node() {
}
node::node(string x) {
	next = NULL;
	license = x;
}
class car {
public:
	void init(string license, int arriving_time);
	~car();
	string license;
	int arriving_time; //unit minutes
};
void car::init(string a, int b) {
	license = a;
	arriving_time = b;
}
car::~car() {
}
class stack {
public:
	stack();
	~stack();
	bool stack_isfull();
	bool stack_isempty();
	bool stack_find(string x);
	void stack_push(string a, int b);
	void stack_pop();
	car *get_top();
	car * num;
	int top;
};
stack::stack() {
	num = new car[all];
	top = -1;
}
stack::~stack() {
}
bool stack::stack_isempty() {
	return top == -1 ? true : false;
}
bool stack::stack_isfull() {
	return top == (all - 1) ? true : false;
}
void stack::stack_push(string a, int b) {
	if (stack_isfull()) {
		cout << "the stack is full" << endl;
	}
	else {
		top++;
		num[top].init(a, b);
	}
}
void stack::stack_pop() {
	if (stack_isempty()) {
		cout << "the stack is empty";
	}
	else {
		top--;
	}
}
bool stack::stack_find(string x) {
	int k = 0;
	for (int i = 0; i <= top; i++) {
		if (num[i].license==x)
		{
			k = 1;
			break;
		}
	}
	return k == 1 ? true : false;
}
car *stack::get_top() {
	if (stack_isempty())
	{
		cout << "this stack is empty";
	}
	else
	{
		return &num[top];
	}
}
class queue {
public:
	queue();
	~queue();
	node *front;
	node *rear;
	int number;
	bool queue_isempty();
	bool queue_find(string x);
	void queue_in(string x);
	node *queue_out();
};
queue::queue() {
	rear = new node("0");
	front = new node("0");
	front->next = rear;
	number = 0;
}
queue::~queue() {
}
bool queue::queue_isempty() {
	return  number == 0 ? true : false;
}
bool queue::queue_find(string x) {
	node *tem = new node("0");
	int k = 0;
	tem = front->next;
	for (int i = 0; i <number; i++) {
		if (tem->license==x)
		{
			k = 1;
			break;
		}
		tem = tem->next;
	}
	return k == 1 ? true : false;
}
void queue::queue_in(string x) {
	rear->license = x;
	node *tem = new node("0");
	rear->next = tem;
	rear = tem;
	number++;
}
node *queue::queue_out() {
	if (queue_isempty()) {
		cout << "the queue is empty";
	}
	else
	{
		node *tem = new node("0");
		tem = front->next;
		front->next = tem->next;
		number--;
		return tem;
	}
}
void tips() {
	cout << "������ʾ:A��ʾ�������� D��ʾ�����뿪 P�鿴��ǰͣ����ͣ������ W�鿴��ǰ���ͣ������ S�鿴������Ϣ E�˳�����" << endl;
}
int arriving() {
	cout << "�����뵽��ʱ�䣨�գ�ʱ���֣�" << endl;
	int day = 0;
	int hour = 0;
	int minute = 0;
	int time = 0;
	cout << "���ڣ�";
	cin >> day;
	cout << "Сʱ��";
	cin >> hour;
	cout << "���ӣ�";
	cin >> minute;
	time = day * 24 * 60 + hour * 60 + minute;
	return time;
}
void show(stack *a, queue *b) {
	cout << endl;
	cout << "��ͣ�������ͣ��������" << all << "����" << endl;
	cout << "��ͣ�����շѱ�׼Ϊ" << fee << "Ԫÿ����" << endl;
	cout << endl;
	cout << "��ǰͣ������" << (a->top + 1) << "����" << endl;
	for (int i = 0; i <= a->top; i++) {
		cout << "����" << (i + 1) << ": " << a->num[i].license << " ����ʱ�䣺" << a->num[i].arriving_time << "��׼����" << endl;
	}
	cout << endl;
	cout << "��ǰ�����" << b->number << "����" << endl;
	node *tem = new node("0");
	tem = b->front->next;
	for (int i = 0; i < b->number; i++)
	{
		cout << "����" << (i + 1) << ": " << tem->license;
		cout << endl;
		tem = tem->next;
	}
	cout << endl;
}
int main() {
	cout << "                                                ��ӭʹ��ͣ��������ϵͳ\n";
	cout << "***********************************************��ͣ�������ͣ������Ϊ" << all << "��************************************************" << endl;
	cout << "*********************************************��ͣ�����շѷ���Ϊ" << fee << "Ԫÿ����***********************************************" << endl;
	cout << "************************************************************************************************************************\n";
	stack *parkinglot = new stack();  //ͣ����ջ
	stack *temp = new stack();  //��ʱջ
	queue *accessroad = new queue();  //���
	string judge1;
	while (1) {
		judge1 = "-1";
		tips();
		cin >> judge1;
		if (judge1 == "E")
		{
			cout << "���򽫽���" << endl;
			exit(1);
		}
		else if (judge1 == "S")
		{
			show(parkinglot, accessroad);
		}
		else if (judge1 == "P")
		{
			cout << "��ǰͣ������" << (parkinglot->top + 1) << "����" << endl;
		}
		else if (judge1 == "W")
		{
			cout << "��ǰ�����" << accessroad->number << "����" << endl;
		}
		else if (judge1 == "A")
		{
			if (parkinglot->stack_isfull())
			{

				cout << "��ǰͣ�������������ĳ�����ͣ�����Ⱥ�" << endl;
				cout << "�����복�ƺ�";
				string tem = "0";
				cin >> tem;
				if (parkinglot->stack_find(tem) || accessroad->queue_find(tem)) {
					cout << "���ƺ�Ϊ" << tem << "�������Ѿ�������ͣ��������,������������ȷ�ĳ��ƺţ��������ϸ��Ϣ���밴S�鿴ͣ����ȫ����Ϣ" << endl;
				}
				else
				{
					accessroad->queue_in(tem);
					cout << "��Ŀǰ�ڱ�����е�" << accessroad->number << "λ" << endl;
				}
			}
			else
			{
				cout << "�����복�ƺ�";
				string tem = "0";
				cin >> tem;
				if (parkinglot->stack_find(tem)) {
					cout << "���ƺ�Ϊ" << tem << "�������Ѿ�������ͣ����,������������ȷ�ĳ��ƺţ��������ϸ��Ϣ���밴S�鿴ͣ����ȫ����Ϣ" << endl;
				}
				else
				{
					parkinglot->stack_push(tem, arriving());
					cout << "ͣ���ɹ���" << endl;
				}
			}
		}
		else if (judge1 == "D")
		{
			cout << "�������뿪�����ĳ��ƺ�" << endl;
			string tem = "0";
			cin >> tem;
			if (parkinglot->stack_find(tem)) {
				while (parkinglot->get_top()->license != tem)
				{
					temp->stack_push(parkinglot->get_top()->license, parkinglot->get_top()->arriving_time);
					parkinglot->stack_pop();
				}
				cout << "�������뿪ʱ�䣨�գ�ʱ���֣�" << endl;
				int day = 0;
				int hour = 0;
				int minute = 0;
				int time = 0;
				cout << "���ڣ�";
				cin >> day;
				cout << "Сʱ��";
				cin >> hour;
				cout << "���ӣ�";
				cin >> minute;
				time = day * 24 * 60 + hour * 60 + minute;
				time = (time - parkinglot->get_top()->arriving_time);
				float cost = time * fee;
				cout << "�������ƺ�Ϊ" << parkinglot->get_top()->license << "��ͣ��" << time << "����,Ӧ��ȡ����" << cost << "Ԫ" << endl;
				parkinglot->stack_pop();
				while (!temp->stack_isempty())
				{
					parkinglot->stack_push(temp->get_top()->license, temp->get_top()->arriving_time);
					temp->stack_pop();
				}
				if (!accessroad->queue_isempty())  //�������Ϊ�գ��г�ʱ
				{
					node *tem = new node("0");
					tem = accessroad->queue_out();
					parkinglot->stack_push(tem->license, time);
					cout << "�����г�����ͣ�����п�λ�����Ŷ���ǰ���ƺ�Ϊ" << tem->license << "��������" << day << "��" << hour << "ʱ" << minute << "��ͣ��ͣ����" << endl;
					delete tem;
				}
			}
			else
			{
				cout << "���ƺ�Ϊ" << tem << "������Ŀǰ����ͣ�������������ϸ��Ϣ���밴S�鿴ͣ����ȫ����Ϣ" << endl;
				if (accessroad->queue_find(tem)) {
					cout << "���ƺ�Ϊ" << tem << "������Ŀǰ�ڱ�����������ϸ��Ϣ���밴S�鿴ͣ����ȫ����Ϣ" << endl;
				}
				else
				{
					cout << "���ƺ�Ϊ" << tem << "������Ŀǰ���ڱ�����������ϸ��Ϣ���밴S�鿴ͣ����ȫ����Ϣ" << endl;
				}
			}
		}
	}
	system("pause");
	return 0;
}