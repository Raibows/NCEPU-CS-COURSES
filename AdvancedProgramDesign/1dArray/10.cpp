#include <iostream>
using namespace std;
int main()
{
	int n, a[100], i(-1), o, t, g;
	cin >> n;
	while (n != 0)
	{
		i++;
		t = n % 10;
		a[i] = t;
		n = n / 10;
	}

	for (g = 0; g <= i; g++)
	{
		for (o = g; o <= i; o++)
		{
			if (a[g] > a[o])
			{
				t = a[g];
				a[g] = a[o];
				a[o] = t;
			}
		}
	}
	n = a[0];
	for (g = 1; g <= i; g++)
	{
		n *= 10;
		n += a[g];
	}
	cout << n << endl;
	return 0;
}
