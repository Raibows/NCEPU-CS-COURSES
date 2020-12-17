#include <iostream>
using namespace std;
int hanshu(int a)
{
	int i, q, w, e = 0, sum = 0;
	for (i = 1; i < a; i++)
	{
		if (a % i == 0)
		{
			sum += i;
		}
	}
	for (i = 1; i < sum; i++)
	{
		if (sum % i == 0)
		{
			e += i;
		}
	}
	if (e == a)
		return sum;
	else
		return 0;
}
int main()
{
	int a;
	cin >> a;
	if (hanshu(a) == 0)
	{
		cout << "no" << endl;
	}
	else
	{
		cout << hanshu(a) << endl;
	}
	return 0;
}
