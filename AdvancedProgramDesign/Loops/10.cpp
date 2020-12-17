#include <iostream>
using namespace std;
int main()
{
	int a, i = 1, b = 1;
	double sum = 0, c = 1;
	cin >> a;
	for (i; i <= a; i++)
	{
		for (b; b <= i; b++)
		{
			c = c * b;
		}

		sum += c;
	}
	cout << sum << endl;
	return 0;
}