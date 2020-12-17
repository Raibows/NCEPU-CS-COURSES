#include <iostream>
using namespace std;
int hanshu(int &a, int &b)
{
	int u, i, o, p;
	u = a % 10;
	i = a / 10 % 10;
	o = b % 10;
	p = b / 10 % 10;
	a = i * 1000 + u + p * 100 + o * 10;
	return a;
}
int main()
{
	int a, b;
	cin >> a >> b;
	cout << hanshu(a, b) << endl;
	return 0;
}
