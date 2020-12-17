#include <iostream>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int *a = new int[n];
    int *b = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        getchar();
    }
    int key;
    cin >> key;
    int low = 0;
    int high = n - 1;
    int mid;
    int tag = 0;
    int i = 0;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (a[mid] < key)
        {
            b[i] = a[mid];
            i++;
            low = mid + 1;
        }
        else if (a[mid] > key)
        {
            b[i] = a[mid];
            i++;
            high = mid - 1;
        }
        else if (a[mid] == key)
        {
            tag = 1;
            b[i] = a[mid];
            i++;
            break;
        }
    }
    if (tag == 0)
    {
        cout << "no" << endl;
        cout << b[0];
        for (int k = 1; k < i; k++)
        {
            cout << "," << b[k];
        }
    }
    else
    {
        cout << mid << endl;
        cout << b[0];
        for (int k = 1; k < i; k++)
        {
            cout << "," << b[k];
        }
    }
    return 0;
}