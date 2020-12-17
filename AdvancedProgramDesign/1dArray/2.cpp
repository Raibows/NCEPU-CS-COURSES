#include <iostream>
using namespace std;
int main()
{
	int a(0), b(0), c(0);
	cin >> a;
	int *k = new int[a];
	for (int i = 0; i < a; i++)
	{
		cin >> k[i];
	}
	for (int q = 0; q < a; q++)
	{
		for (int o = 0; o < a; o++)
		{
			if (k[q] > k[o])
			{
				goto loop;
			}
		}
		b = k[q];
		c = q;
		break;
	loop:;
	}

	for (int w = 0; w < a; w++)
	{
		for (int o = 0; o < a; o++)
		{
			if (k[w] < k[o])
			{
				goto haa;
			}
		}
		k[c] = k[w];
		k[w] = b;
		break;
	haa:;
	}
	for (int e = 0; e < a; e++)
	{
		cout << k[e] << " ";
	}
	cout << endl;

	return 0;
}