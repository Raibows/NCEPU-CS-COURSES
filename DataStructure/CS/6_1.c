#include <stdio.h>

int main(void)
{
	int o = 0;
	scanf("%d", &o);
	int n[100];
	int i = 0;
	for (i = 0; i < o; i++)
	{
		scanf("%d", &n[i]);
	}
	int x, y, z;
	x = 10000;
	y = 10000;
	z = 0;
	i = 0;
	for (i = 0; i < o - 1; i++)
	{
		int j = 0;
		for (j = 0; j < o; j++)
		{
			if (n[j] != 10000)
			{
				if (x > n[j])
				{
					x = n[j] + x;
					n[j] = x - n[j];
					x = x - n[j];
				}
			}
		}
		int k = 0;
		for (k = 0; k < o; k++)
		{
			if (n[k] != 10000)
			{
				if (y > n[k])
				{
					y = n[k] + y;
					n[k] = y - n[k];
					y = y - n[k];
				}
			}
		}
		z = z + x + y;
		int l = 0;
		for (l = 0; l < o; l++)
		{
			if (n[l] == 10000)
			{
				n[l] = x + y;
				x = 10000;
				y = 10000;
				break;
			}
		}
	}

	printf("%d", z);
	return 0;
}