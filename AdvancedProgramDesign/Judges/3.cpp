#include <iostream>
using namespace std;
int main()
{
    char a, b, c, d, e;
    cin >> a >> b >> c >> d >> e;
    a = a + 4;
    b = b + 4;
    c = c + 4;
    d = d + 4;
    e = e + 4;
    if (a > 122)
    {
        a = a - 26;
    }
    if (b > 122)
    {
        b = b - 26;
    }
    if (c > 122)
    {
        c = c - 26;
    }
    if (d > 122)
    {
        d = d - 26;
    }
    if (e > 122)
    {
        e = e - 26;
    }
    cout << a << b << c << d << e << endl;

    return 0;
}
