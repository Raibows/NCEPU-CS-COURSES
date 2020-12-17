#include <iostream>
using namespace std;
double hanshu(int i)
{
	double a;
	if (i % 2 == 0)
		a = -1 / (double(i) * (double(i) + 1));
	else
		a = 1 / (double(i) * (double(i) + 1));
	return a;
}
int main()
{
	double k, sum;
	int i = 0;
	cin >> k;
	sum = 0;
	for (i = 1; i <= k; i++)
	{
		sum += hanshu(i);
	}
	cout << sum << endl;
	return 0;
}
