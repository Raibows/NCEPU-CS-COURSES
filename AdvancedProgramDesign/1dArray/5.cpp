#include <iostream>
using namespace std;
int main()
{
	int n;
	cin >> n;
	int *k = new int[n + 1];
	for (int i = 0; i < n; i++)
	{
		cin >> k[i];
	}
	k[n] = k[0];
	for (int a = 0; a < n; a++)
	{
		k[a] = k[a + 1];
	}
	for (int b = 0; b < n; b++)
	{
		cout << k[b] << " ";
	}
	cout << endl;
}