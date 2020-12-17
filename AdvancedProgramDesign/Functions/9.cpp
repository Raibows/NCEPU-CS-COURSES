#include <iostream>
using namespace std;
int hanshu1(int a)
{
	int b = 0, q;
	while (a > 0)
	{
		q = a % 10;
		a = a / 10;
		if (q == 1)
			b++;
	}
	return b;
}
int hanshu2(int a)
{
	int b = 0, q;
	while (a > 0)
	{
		q = a % 10;
		a = a / 10;
		if (q == 2)
			b++;
	}
	return b;
}
int hanshu3(int a)
{
	int b = 0, q;
	while (a > 0)
	{
		q = a % 10;
		a = a / 10;
		if (q == 3)
			b++;
	}
	return b;
}
int main()
{
	int a;
	cin >> a;
	cout << hanshu1(a) << " " << hanshu2(a) << " " << hanshu3(a) << endl;
	return 0;
}
