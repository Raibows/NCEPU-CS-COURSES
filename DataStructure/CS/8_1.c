#include <stdio.h>

int main(void)
{
    int n;
    scanf("%d", &n);
    int a[999];
    int b[999];
    int i;
    for (i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
        getchar();
    }
    int key;
    scanf("%d", &key);
    int low, high, mid, tag, bn;
    low = 0;
    bn = 0;
    high = n - 1;
    tag = 0;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (a[mid] < key)
        {
            b[bn] = a[mid];
            bn++;
            low = mid + 1;
        }
        else if (a[mid] > key)
        {
            b[bn] = a[mid];
            bn++;
            high = mid - 1;
        }
        else if (a[mid] == key)
        {
            tag = 1;
            b[bn] = a[mid];
            bn++;
            break;
        }
    }
    if (tag == 0)
    {
        printf("no\n%d", b[0]);
        for (i = 1; i < bn; i++)
        {
            printf(",%d", b[i]);
        }
    }
    else
    {
        printf("%d\n%d", mid, b[0]);
        for (i = 1; i < bn; i++)
        {
            printf(",%d", b[i]);
        }
    }
}