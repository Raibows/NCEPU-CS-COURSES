#include <iostream>
using namespace std;
int main()
{
    float n, a, b, c;
    cin >> n;
    a = 2;
    b = 1;
    c = 0;
    float k[n];
    for (int i = 0; i < n; i++)
    {
        a = a + i;
        b = b + i;
        k[i] = a / b;
        c += k[i];
    }
    cout << c << endl;
    return 0;
}
