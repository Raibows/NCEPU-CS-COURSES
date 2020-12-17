#include <cstdio>

struct node
{
    int val;
    node *next;
    node(int v, node *n)
    {
        val = v;
        next = n;
    }
};

const int dict_max = 10;
node *arr[dict_max];

void insert()
{
    int val;
    scanf("%d", &val);
    int hash = val % dict_max;
    node *temp = new node(val, NULL);
    if (arr[hash] == NULL)
        arr[hash] = temp;
    else
    {
        node *cur = arr[hash];
        while (cur->next != NULL)
        {
            if (cur->val == val)
                break;
            cur = cur->next;
        }
        cur->next = temp;
    }
    printf("insert %d successfully\n", val);
}

void query()
{
    int val;
    scanf("%d", &val);
    int hash = val % dict_max;
    node *cur = arr[hash];
    while (cur != NULL)
    {
        if (cur->val == val)
        {
            printf("query %d successfully\n", val);
            return;
        }
        cur = cur->next;
    }
    printf("%d not found!\n", val);
}

void del()
{
    int val;
    scanf("%d", &val);
    int hash = val % dict_max;
    node *cur = arr[hash];
    bool flag = false;
    while (cur != NULL)
    {
        if (cur->next && cur->next->val == val)
        {
            flag = true;
            node *temp = cur->next;
            cur->next = temp->next;
            delete temp;
            break;
        }
        cur = cur->next;
    }
    if (flag)
        printf("%d has been deleted\n", val);
    else
        printf("%d not found!\n", val);
}
int main(int argc, char *argv[])
{
    char op = '1';
    const char *tip = "1. e:exit\n2. i:insert\n3. q:query\n4. d:delete\n";
    printf("%s", tip);
    while (scanf("%c", &op) && op != 'e')
    {
        if (op == EOF || op == '\n')
            continue;
        switch (op)
        {
        case 'i':
            insert();
            break;
        case 'q':
            query();
            break;
        case 'd':
            del();
            break;
        }
        printf("%s", tip);
    }

    return 0;
}
