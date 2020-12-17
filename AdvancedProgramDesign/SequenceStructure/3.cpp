#include <cmath>
#include <iostream>
using namespace std;
int main()
{
   double a, b, c, d, s;
   cin >> a >> b >> c;
   d = (a + b + c) / 2;
   s = sqrt(d * (d - a) * (d - b) * (d - c));
   cout << s << endl;
   return 0;
}
