#include <iostream>
using namespace std;
int main()
{
	char ch;
	int i, sum = 0;
	char a[9999];
	for (i = 0;; i++)
	{
		cin >> ch;
		if (ch != '0')
		{
			a[i] = ch;
			sum += a[i];
		}
		else
		{
			break;
		}
	}

	cout << sum << endl;
	return 0;
}
