#include <iostream>
#include <cstring>
using namespace std;
int main()
{
	char a[100];
	int i, n;
	cin >> a;
	n = strlen(a);
	for (i = 0; i < n; i++)
	{
		if (a[i] < 'a')
		{
			if (a[i] < 'W')
			{
				a[i] = a[i] + 4;
			}
			else
			{
				a[i] = a[i] - 22;
			}
		}
		else
		{
			if (a[i] < 'w')
			{
				a[i] = a[i] + 4;
			}
			else
			{
				a[i] = a[i] - 22;
			}
		}
	}
	cout << a << endl;
	return 0;
}
