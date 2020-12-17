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
class Linklist
{
public:
    Linklist();
    ~Linklist();
    int getlength();
    Node *find(int x);
    void create();

private:
    Node *head;
};
Linklist::Linklist()
{
    Node *head = new Node(0);
}
Linklist::~Linklist()
{
}
int Linklist::getlength()
{
    int k = 0;
    Node *tem = new Node(0);
    tem = head->next;
    while (tem != NULL)
    {
        k++;
        tem = tem->next;
    }
    return k;
}
Node *Linklist::find(int x)
{
    int k = 0;
    Node *tem = new Node(0);
    tem = head;
    while ((k != x) && (tem->next != NULL))
    {
        tem = tem->next;
        k++;
    }
    return tem;
}
void Linklist::create()
{
    Node *tem = new Node(0);
    tem = head;
    char a;
    for (int i = 0; a = cin.get() != '\n'; i++)
    {
        Node *q = new Node(0);
        cin.unget();
        cin >> q->data;
        tem->next = q;
        tem = q;
        q->~Node();
    }
}

int main()
{
    Linklist *l = new Linklist();
    int k = 0;
    cout << "以回车作结束" << endl;
    cin >> k;
    l->create();
    if (l->getlength() < k)
    {
        cout << "Not Found" << endl;
    }
    else
    {
        k = l->getlength() - k + 1;
        cout << (l->find(k))->data << endl;
    }
    return 0;
}