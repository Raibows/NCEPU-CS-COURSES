#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	int n, s(0);
	cin >> n;
	for (int i = 1; i < n; i++)
	{
		s = 0;
		for (int k = 1; k < i; k++)
		{
			if (i % k == 0)
			{
				s += k;
			}
		}
		if (i == s)
			cout << i << " ";
	}
	return 0;
}
