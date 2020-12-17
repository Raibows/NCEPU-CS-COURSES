#include <iostream>
using namespace std;
int main()
{
   int a, b, c;
   cin >> a >> b >> c;
   if (a - b >= 0 && a - c >= 0)
   {
      cout << a << endl;
   }
   else if (b - a >= 0 && b - c >= 0)
   {
      cout << b << endl;
   }
   else
   {
      cout << c << endl;
   }
   return 0;
}
