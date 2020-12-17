#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
	int n, a[100], b[100], c(0), d(-1), x = 0, y = 0;
	int h, j;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	sort(a, a + n);
	for (int o = 0; o < n; o++)
	{
		c = 0;
		d++;
		for (int p = 0; p < n; p++)
		{
			if (a[o] == a[p])
			{
				c++;
				b[d] = c;
			}
		}
	}
	for (int g = 0; g < n; g++)
	{
		x = 0, y = 0;
		for (h = g - 1; h >= 0; h--)
			if (a[g] == a[h])
			{
				x = 1;
			}
		if (x == 1)
			continue;

		for (j = 0; j < n; j++)
			if (b[g] < b[j])
			{
				y = 1;
			}
		if (y == 1)
			continue;
		cout << a[g] << " " << b[g];
		cout << endl;
	}
	return 0;
}
