#include <iostream>
using namespace std;
float sushu(float a)
{
	float t = 0, sum = 0;
	int i, g;
	for (i = 2; i <= a; i++)
	{
		t = 0;
		for (g = 2; g < i; g++)
		{
			if (i % g == 0)
				t = 1;
		}
		if (t == 1)
			continue;
		t = i;
		sum += (1 / t);
	}
	return sum;
}
int main()
{
	float a, b;
	cin >> a;
	cout << sushu(a);
	return 0;
}
