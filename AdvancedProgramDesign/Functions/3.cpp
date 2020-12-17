#include <iostream>
using namespace std;
int sushu(int a)
{
	int b, i = 0, o = 0, p = 0, t = 0, y = 0;
	for (i = 2; i < a; i++)
	{
		t = 0;
		for (o = 2; o < i; o++)
		{
			if (i % o == 0)
			{
				t = 1;
				break;
			}
		}
		if (t == 1)
		{
			continue;
		}
		for (p = i; p + i <= a; p++)
		{
			t = 0;
			for (y = 2; y < p; y++)
			{
				if (p % y == 0)
				{
					t = 1;
					break;
				}
			}
			if (t == 1)
			{
				continue;
			}
			if (i + p == a)
			{
				t = 2;
				break;
			}
		}
		if (t == 2)
		{
			break;
		}
	}
	b = i;
	return b;
}
int main()
{
	int a;
	cin >> a;
	cout << a << "=" << sushu(a) << "+" << a - sushu(a) << endl;
	return 0;
}
