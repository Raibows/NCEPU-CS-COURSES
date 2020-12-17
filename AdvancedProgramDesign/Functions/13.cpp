#include <iostream>
#include <cmath>
using namespace std;
int hanshu(int a)
{
	int i, b, c = 0;
	for (i = 0; a > 0; i++)
	{
		b = a % 8;
		a = a / 8;
		c += b * (int)pow(10, i);
	}
	return c;
}
int main()
{
	int n;
	cin >> n;
	cout << hanshu(n) << endl;
	return 0;
}
