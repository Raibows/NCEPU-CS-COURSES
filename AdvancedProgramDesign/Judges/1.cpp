#include <iostream>
#include <math.h>
using namespace std;
int main()
{
	float x, y;
	cin >> x;
	if (x <= -1)
	{
		y = 2 * x + cos(x);
	}
	else if (x > -1 && x < 1)
	{
		y = 1 / pow((x + 1), 2.0 / 3);
	}
	else if (x >= 1)
	{
		y = sin(x) * sin(x);
	}
	cout << y << endl;
	return 0;
}
