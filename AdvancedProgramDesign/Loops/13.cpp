#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	int m, n;
	double c(0), s(0);
	cin >> m >> n;
	if (m == 1)
	{
		c = -1;
		s = -1;
	}
	for (int i = m; i <= n; i++)
	{
		for (int k = 2; k < i; k++)
		{
			if (i % k == 0)
			{
				goto loop;
			}
		}
		c = c + 1;
		s += i;
	loop:;
	}
	if (c == 0)
	{
		cout << "no" << endl;
	}
	else
	{
		s = s / c;
		cout << c << " " << s << endl;
	}
	return 0;
}
