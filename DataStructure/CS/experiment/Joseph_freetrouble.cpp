#include <iostream>
using namespace std;
class Node
{
public:
    Node(int x);
    ~Node();
    int data;
    Node *next;
};
Node::Node(int x)
{
    data = x;
    next = NULL;
}
Node::~Node()
{
}
class linklist
{
public:
    int nn;
    linklist();
    void find(int position);
    void create(int n);
    void freetrouble(int position);

private:
    Node *head;
};
linklist::linklist()
{
    head = new Node(0);
}
void linklist::create(int n)
{
    nn = n;
    Node *tem = new Node(0);
    tem = head;
    while (n > 1)
    {
        Node *p = new Node(0);
        cin >> p->data;
        tem->next = p;
        tem = p;
        p->~Node();
        n--;
    }
    Node *p = new Node(0);
    cin >> p->data;
    tem->next = p;
    tem = p;
    tem->next = head;
    p->~Node();
    tem->~Node();
}
void linklist::find(int position)
{
    Node *tem = new Node(0);
    Node *pre = new Node(0);
    tem = head->next;
    while (position > 1)
    {
        pre = tem;
        tem = tem->next;
        if (tem != head)
        {
            position--;
        }
    }
    Node *last = new Node(0);
    last = tem;
    while (last->next != head)
    {
        last = last->next;
    }

    if (pre != head)
    {
        if (last == tem)
        {
            pre->next = head;
        }
        else
        {
            last->next = head->next;
            pre->next = head;
            head->next = tem->next;
        }
    }
    else
    {
        if (last == tem)
        {
            pre->next = head;
        }
        else
        {
            pre->next = tem->next;
            last->next = head;
        }
    }
    cout << tem->data;
    delete tem;
}
void linklist::freetrouble(int position)
{
    Node *tem = new Node(0);
    Node *pre = new Node(0);
    tem = head->next;
    pre = tem;
    int tag = 0;
    while (head->next != head && tag != nn)
    {
        int i = 1;
        for (i; i < position; i++)
        {
            pre = tem;
            tem = tem->next;
            if (tem == head)
            {
                i--;
            }
        }
        pre->next = tem->next;
        cout << tem->data;
        tag++;
        tem = tem->next;
        if (tem == head)
        {
            tem = tem->next;
        }
        pre = tem;
    }
}
int main()
{
    int m, n;
    cin >> m >> n;
    linklist *l = new linklist();
    l->create(n);
    l->freetrouble(m);
    cout << endl;
    return 0;
}