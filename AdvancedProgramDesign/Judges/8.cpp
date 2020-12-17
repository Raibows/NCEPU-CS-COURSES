#include <iostream>
using namespace std;
int main()
{
	int a, b, c, d;
	cin >> a;
	b = a % 10;
	c = a / 10 % 10;
	d = a / 100;
	if (a < 100)
	{
		cout << "NO" << endl;
	}

	else if (a == b * b * b + c * c * c + d * d * d)
	{
		cout << "YES" << endl;
	}
	else
	{
		cout << "NO" << endl;
	}
	return 0;
}
