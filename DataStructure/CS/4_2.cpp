#include <iostream>
using namespace std;
int main()
{
    int array[1000];
    cin >> array[0];
    int tem = array[0];
    int count = 1;
    char a = '0';
    for (int i = 1; a = cin.get() != '\n'; i++)
    {
        cin.unget();
        cin >> array[i];
        if (array[i] == tem)
        {
            count++;
        }
        else
        {
            count--;
            if (count < 0)
            {
                tem = array[i];
                count = 1;
            }
        }
    }
    if (count >= 1)
    {
        cout << tem;
    }
    else
    {
        cout << -1;
    }
    return 0;
}