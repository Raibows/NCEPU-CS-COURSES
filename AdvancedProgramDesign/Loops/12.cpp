#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	int a, b, c, d;
	cin >> a >> b;
	if (a <= b)
	{
		c = a;
		d = b;
	}
	else
	{
		c = b;
		d = a;
	}
	for (c;; c--)
	{
		if (a % c == 0 && b % c == 0)
		{
			break;
		}
	}
	for (d;; d++)
	{
		if (d % a == 0 && d % b == 0)
		{
			break;
		}
	}
	cout << c << " " << d << endl;
	return 0;
}
