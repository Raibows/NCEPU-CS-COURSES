#include <iostream>
using namespace std;
int main()
{
	int n, a(1), b(2), c, d;
	cin >> n;
	for (; b <= 9; b++)
	{
		for (a = 1; a < b; a++)
		{
			c = a * 10 + b;
			d = b * 10 + a;
			if ((c * d) == n)
			{
				goto loop;
			}
		}
	}
	cout << "no" << endl;
loop:
	cout << a << b << endl;
	return 0;
}
