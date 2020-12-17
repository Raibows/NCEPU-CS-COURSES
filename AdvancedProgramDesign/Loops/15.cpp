#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	double n, a(0), b(0), c = 0;
	cin >> n;
	{
		for (int i = 2; i <= n; i++)
		{
			for (int k = 2; k < i; k++)
			{
				if (i % k == 0)
				{
					goto loop;
				}
			}
			a = i;
			b += (1 / a);
		loop:;
		}
		cout << b << endl;
	}
	return 0;
}
