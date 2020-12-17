#include <iostream>
#include <stdio.h>
using namespace std;
int main()
{
	int a[100], n, i, j, k, b[100], c[100] = {0}, gs = 0, cz = 0, max = 0, t;
	cin >> n;
	for (i = 0; i < n; i++)
		cin >> a[i]; //输入n个数
	for (i = 0; i < n; i++)
		for (j = 0; j < n - 1; j++)
			if (a[j] > a[j + 1])
			{
				t = a[j];
				a[j] = a[j + 1];
				a[j + 1] = t;
			}
	//for(i=0;i<n;i++) cout<<a[i]<<" ";
	for (i = 0; i < n; i++) //对数组a的每一个元素
	{
		cz = 0; //判断是否在b数组中出现
		for (j = 0; j < gs; j++)
			if (a[i] == b[j]) //如果出现了的话，且下标为j
			{
				cz = 1; //则存在
				break;	//并结束
			}
		if (cz == 0) //如果不存在
		{
			b[gs] = a[i]; //则将a[i]放到b数组中
			c[gs]++;	  //对应的a[i]出现的次数加一
			gs++;		  //b数组中元素个数加一
		}
		else //如果存在的话
		{
			c[j]++; //则j为a[i]在b数组的下标，对应c数组中元素个数加一
		}
	}
	for (i = 0; i < gs; i++) //c数组中找出现的次数最大值
		if (c[i] > max)
			max = c[i];

	for (i = 0; i < gs; i++)
	{
		if (c[i] == max) //输出对应的b数组中的数
			cout << b[i] << " " << max << endl;
	}
}
