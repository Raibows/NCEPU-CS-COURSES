#include <iostream>
using namespace std;
void hanshu(int &a, int &b)
{
	int i = 0, o = 0, p = 0;
	if (a < b)
		p = a;
	else
		p = b;
	for (i = p; i >= 1; i--)
	{
		if (a % i == 0 && b % i == 0)
		{
			break;
		}
	}
	for (o = p;; o++)
	{
		if (o % a == 0 && o % b == 0)
		{
			break;
		}
	}
	a = i;
	b = o;
}
int main()
{
	int a, b;
	cin >> a >> b;
	hanshu(a, b);
	cout << a << " " << b;
	return 0;
}
