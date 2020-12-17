#include <iostream>
using namespace std;
int main()
{
	int a, c[100], i, g;
	float t = 0, b = 0;
	for (i = 0;; i++)
	{
		cin >> c[i];
		if (c[i] <= 0)
		{
			break;
		}
	}
	for (g = 0; g < i; g++)
	{
		t += c[g];
	}
	b = t / i;
	cout << b << endl;
	for (g = 0; g < i; g++)
	{
		if (c[g] < b)
		{
			cout << c[g] << " ";
		}
	}
	cout << endl;
	return 0;
}