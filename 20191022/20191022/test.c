
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int num(int n)
{
	if (n == 0)
	{
		return 0;
	}
	if (n == 1)
	{
		return 1;

	}
	if (n % 2 == 0)
	{
		return n + num(n / 2);
	}
	else
	{
		return (n - 1) + num((n / 2) + 1);
	}
}

int main()
{
	int n = 0;
	printf("请问你要花费多少钱？\n");
	scanf("%d", &n);
	printf("%d元可以喝%d瓶汽水！！\n", n, num(n));
	system("pause");
	return 0;
}