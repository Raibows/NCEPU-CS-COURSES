// ConsoleApplication10.cpp: 定义控制台应用程序的入口点。
//#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;
const float fee = 10; //10 yuan per minute
const int all = 2;	  //parkinglot max is 2
class node
{
public:
	node(string x);
	~node();
	string license;
	node *next;
};
node::~node()
{
}
node::node(string x)
{
	next = NULL;
	license = x;
}
class car
{
public:
	void init(string license, int arriving_time);
	~car();
	string license;
	int arriving_time; //unit minutes
};
void car::init(string a, int b)
{
	license = a;
	arriving_time = b;
}
car::~car()
{
}
class stack
{
public:
	stack();
	~stack();
	bool stack_isfull();
	bool stack_isempty();
	bool stack_find(string x);
	void stack_push(string a, int b);
	void stack_pop();
	car *get_top();
	car *num;
	int top;
};
stack::stack()
{
	num = new car[all];
	top = -1;
}
stack::~stack()
{
}
bool stack::stack_isempty()
{
	return top == -1 ? true : false;
}
bool stack::stack_isfull()
{
	return top == (all - 1) ? true : false;
}
void stack::stack_push(string a, int b)
{
	if (stack_isfull())
	{
		cout << "the stack is full" << endl;
	}
	else
	{
		top++;
		num[top].init(a, b);
	}
}
void stack::stack_pop()
{
	if (stack_isempty())
	{
		cout << "the stack is empty";
	}
	else
	{
		top--;
	}
}
bool stack::stack_find(string x)
{
	int k = 0;
	for (int i = 0; i <= top; i++)
	{
		if (num[i].license == x)
		{
			k = 1;
			break;
		}
	}
	return k == 1 ? true : false;
}
car *stack::get_top()
{
	if (stack_isempty())
	{
		cout << "this stack is empty";
	}
	else
	{
		return &num[top];
	}
}
class queue
{
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
queue::queue()
{
	rear = new node("0");
	front = new node("0");
	front->next = rear;
	number = 0;
}
queue::~queue()
{
}
bool queue::queue_isempty()
{
	return number == 0 ? true : false;
}
bool queue::queue_find(string x)
{
	node *tem = new node("0");
	int k = 0;
	tem = front->next;
	for (int i = 0; i < number; i++)
	{
		if (tem->license == x)
		{
			k = 1;
			break;
		}
		tem = tem->next;
	}
	return k == 1 ? true : false;
}
void queue::queue_in(string x)
{
	rear->license = x;
	node *tem = new node("0");
	rear->next = tem;
	rear = tem;
	number++;
}
node *queue::queue_out()
{
	if (queue_isempty())
	{
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
void tips()
{
	cout << "操作提示:A表示车辆到达 D表示车辆离开 P查看当前停车场停车总数 W查看当前便道停车总数 S查看所有信息 E退出程序" << endl;
}
int arriving()
{
	cout << "请输入到达时间（日：时：分）" << endl;
	int day = 0;
	int hour = 0;
	int minute = 0;
	int time = 0;
	cout << "日期：";
	cin >> day;
	cout << "小时：";
	cin >> hour;
	cout << "分钟：";
	cin >> minute;
	time = day * 24 * 60 + hour * 60 + minute;
	return time;
}
void show(stack *a, queue *b)
{
	cout << endl;
	cout << "本停车场设计停车总数有" << all << "辆车" << endl;
	cout << "本停车场收费标准为" << fee << "元每分钟" << endl;
	cout << endl;
	cout << "当前停车场有" << (a->top + 1) << "辆车" << endl;
	for (int i = 0; i <= a->top; i++)
	{
		cout << "车辆" << (i + 1) << ": " << a->num[i].license << " 进场时间：" << a->num[i].arriving_time << "标准分钟" << endl;
	}
	cout << endl;
	cout << "当前便道有" << b->number << "辆车" << endl;
	node *tem = new node("0");
	tem = b->front->next;
	for (int i = 0; i < b->number; i++)
	{
		cout << "车辆" << (i + 1) << ": " << tem->license;
		cout << endl;
		tem = tem->next;
	}
	cout << endl;
}
int main()
{
	cout << "                                                欢迎使用停车场管理系统\n";
	cout << "***********************************************此停车场设计停车总数为" << all << "辆************************************************" << endl;
	cout << "*********************************************此停车场收费费用为" << fee << "元每分钟***********************************************" << endl;
	cout << "************************************************************************************************************************\n";
	stack *parkinglot = new stack(); //停车场栈
	stack *temp = new stack();		 //临时栈
	queue *accessroad = new queue(); //便道
	string judge1;
	while (1)
	{
		judge1 = "-1";
		tips();
		cin >> judge1;
		if (judge1 == "E")
		{
			cout << "程序将结束" << endl;
			exit(1);
		}
		else if (judge1 == "S")
		{
			show(parkinglot, accessroad);
		}
		else if (judge1 == "P")
		{
			cout << "当前停车场有" << (parkinglot->top + 1) << "辆车" << endl;
		}
		else if (judge1 == "W")
		{
			cout << "当前便道有" << accessroad->number << "辆车" << endl;
		}
		else if (judge1 == "A")
		{
			if (parkinglot->stack_isfull())
			{

				cout << "当前停车场已满，您的车辆将停入便道等候！" << endl;
				cout << "请输入车牌号";
				string tem = "0";
				cin >> tem;
				if (parkinglot->stack_find(tem) || accessroad->queue_find(tem))
				{
					cout << "车牌号为" << tem << "的汽车已经存在于停车场或便道,请重新输入正确的车牌号！如需更详细信息，请按S查看停车场全部信息" << endl;
				}
				else
				{
					accessroad->queue_in(tem);
					cout << "您目前在便道排列第" << accessroad->number << "位" << endl;
				}
			}
			else
			{
				cout << "请输入车牌号";
				string tem = "0";
				cin >> tem;
				if (parkinglot->stack_find(tem))
				{
					cout << "车牌号为" << tem << "的汽车已经存在于停车场,请重新输入正确的车牌号！如需更详细信息，请按S查看停车场全部信息" << endl;
				}
				else
				{
					parkinglot->stack_push(tem, arriving());
					cout << "停车成功！" << endl;
				}
			}
		}
		else if (judge1 == "D")
		{
			cout << "请输入离开汽车的车牌号" << endl;
			string tem = "0";
			cin >> tem;
			if (parkinglot->stack_find(tem))
			{
				while (parkinglot->get_top()->license != tem)
				{
					temp->stack_push(parkinglot->get_top()->license, parkinglot->get_top()->arriving_time);
					parkinglot->stack_pop();
				}
				cout << "请输入离开时间（日：时：分）" << endl;
				int day = 0;
				int hour = 0;
				int minute = 0;
				int time = 0;
				cout << "日期：";
				cin >> day;
				cout << "小时：";
				cin >> hour;
				cout << "分钟：";
				cin >> minute;
				time = day * 24 * 60 + hour * 60 + minute;
				time = (time - parkinglot->get_top()->arriving_time);
				float cost = time * fee;
				cout << "汽车车牌号为" << parkinglot->get_top()->license << "共停车" << time << "分钟,应收取费用" << cost << "元" << endl;
				parkinglot->stack_pop();
				while (!temp->stack_isempty())
				{
					parkinglot->stack_push(temp->get_top()->license, temp->get_top()->arriving_time);
					temp->stack_pop();
				}
				if (!accessroad->queue_isempty()) //当便道不为空，有车时
				{
					node *tem = new node("0");
					tem = accessroad->queue_out();
					parkinglot->stack_push(tem->license, time);
					cout << "因便道有车，且停车场有空位，故排队最前车牌号为" << tem->license << "的汽车于" << day << "日" << hour << "时" << minute << "分停入停车场" << endl;
					delete tem;
				}
			}
			else
			{
				cout << "车牌号为" << tem << "的汽车目前不在停车场，如需更详细信息，请按S查看停车场全部信息" << endl;
				if (accessroad->queue_find(tem))
				{
					cout << "车牌号为" << tem << "的汽车目前在便道，如需更详细信息，请按S查看停车场全部信息" << endl;
				}
				else
				{
					cout << "车牌号为" << tem << "的汽车目前不在便道，如需更详细信息，请按S查看停车场全部信息" << endl;
				}
			}
		}
	}
	system("pause");
	return 0;
}