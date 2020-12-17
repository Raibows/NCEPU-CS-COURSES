#include <iostream>
using namespace std;
int main()
{
	int a, b, c;
	cin >> a;
	b = a % 3;
	c = a % 7;
	if (b == 0 && c == 0)
	{
		cout << "3" << endl;
	}
	else if (b == 0)
	{
		cout << "1" << endl;
	}
	else if (c == 0)
	{
		cout << "2" << endl;
	}
	else
	{
		cout << "4" << endl;
	}
	return 0;
}
