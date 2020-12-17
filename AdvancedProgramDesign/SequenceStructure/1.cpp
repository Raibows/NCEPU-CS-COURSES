#include <iostream>
using namespace std;
int main()
{
	int shi, wu, er, yi, y;
	cin >> y;
	shi = y / 10;
	wu = y % 10 / 5;
	er = y % 10 % 5 / 2;
	yi = y % 10 % 5 % 2;
	cout << shi << " " << wu << " " << er << " " << yi << " " << endl;
	return 0;
}
