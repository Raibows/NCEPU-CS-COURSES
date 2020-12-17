#include <iostream>
using namespace std;
int main()
{
	int n, c, a[100], i, l, h, m, t(0);
	cin >> n;
	for (i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	cin >> c;
	l = 0;
	h = n - 1;
	for (i = 1;; i++)
	{
		m = (l + h) / 2;
		if (m > h || m < l)
		{
			t = 2;
			break;
		}
		if (a[m] == c)
		{
			t = 1;
			break;
		}
		if (l == h)
		{
			t = 0;
			break;
		}
		if (a[m] < c)
		{
			l = m + 1;
		}
		if (a[m] > c)
		{
			h = m - 1;
		}
	}
	if (t == 1)
	{
		cout << m << endl
			 << i << endl;
	}
	if (t == 0)
	{
		cout << "no" << endl
			 << i << endl;
	}
	if (t == 2)
	{
		cout << "no" << endl
			 << i - 1 << endl;
	}
	return 0;
}
