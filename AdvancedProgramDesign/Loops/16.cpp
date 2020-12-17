#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	int n, a, s(0), b(0);
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		a = i;
		b = i;
		if (a % 7 != 0)
		{
			for (; a > 0;)
			{
				if (a % 10 == 7)
				{
					b = 0;
				}
				a = a / 10;
			}
			s = (s + b * b);
		}
	}
	cout << s << endl;
	return 0;
}
