#include <stdio.h>
int x = 0;
void swap(int *a, int b, int c)
{
    int tem = a[b];
    a[b] = a[c];
    a[c] = tem;
}
int pivortation(int *a, int low, int high)
{
    int pivort = a[low];
    while (low < high)
    {
        while (low < high && a[high] >= pivort)
        {
            high--;
        }
        swap(a, low, high);
        while (low < high && a[low] <= pivort)
        {
            low++;
        }
        swap(a, low, high);
    }
    return low;
}
void quicksort(int *a, int low, int high)
{
    int pivort = pivortation(a, low, high);
    if (x == 0)
    {
        printf("%d ", pivort + 1);
        x++;
    }
    if (low <= high)
    {
        quicksort(a, low, pivort - 1);
        quicksort(a, pivort + 1, high);
    }
}

int main(void)
{
    int a[6];
    int n = 0;
    scanf("%d", &n);
    int i = 0;
    for (i; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    quicksort(a, 0, n - 1);
    for (i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
}