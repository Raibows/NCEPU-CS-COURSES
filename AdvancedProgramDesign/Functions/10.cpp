#include <iostream>
using namespace std;
int hanshu(int k[], int n)
{
	int i, max, min, t, a = 0, b = 1, sum = 0;
	max = k[0];
	min = k[1];
	for (i = 0; i < n; i++)
	{
		if (k[i] > max)
		{
			max = k[i];
			a = i;
		}
		if (k[i] < min)
		{
			min = k[i];
			b = i;
		}
	}
	k[a] = min;
	k[b] = max;
	for (i = 0; i < n; i++)
	{
		sum += k[i];
	}
	return sum;
}
int main()
{

	int k[50], i, n, sum;
	cin >> n;
	for (i = 0; i < n; i++)
	{
		cin >> k[i];
	}
	sum = hanshu(k, n);
	for (i = 0; i < n; i++)
	{
		cout << k[i] << " ";
	}
	cout << endl
		 << sum << endl;
	return 0;
}
