#include <iostream>
using namespace std;
int main()
{
   int a, b, min;
   cin >> a;
   int k[a];
   for (int i = 0; i < a; i++)
   {
      cin >> b;
      k[i] = b;
   }
   min = k[0];
   for (int c = 0; c < a; c++)
   {

      if (min > k[c])
      {
         min = k[c];
      }
   }
   cout << min << endl;
   return 0;
}
