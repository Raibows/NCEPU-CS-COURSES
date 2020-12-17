#include <iostream>
#include <cmath>
using namespace std;
int hanshu(int a)
{
	int i = 0, b, c, d;
	if (a < 10)
	{
		return 0;
	}
	c = a;
	while (a > 0)
	{
		b = a % 10;
		a = a / 10;
		i++;
	}
	d = b;
	for (a = 0; a < i - 1; a++)
	{
		d = d * 10;
	}
	d = c - d;
	return d;
}
int main()
{
	int a;
	cin >> a;
	cout << hanshu(a) << endl;
	return 0;
}
