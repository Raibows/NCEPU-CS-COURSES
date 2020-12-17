#include <iostream>
#include <math.h>
using namespace std;
int main()
{
	float x, y;
	cin >> x;
	if (x <= -1)
	{
		y = 3 * sqrt(fabs(x) + 2) + 1;
	}
	else if (x > -1 && x <= 10)
	{
		y = 1 + x * x * x * x * x;
	}
	else if (x > 10)
	{
		y = sqrt((x + 1) / (2 * x * x));
	}
	cout << y << endl;
	return 0;
}
