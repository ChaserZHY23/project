#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
int main()
{
	int n = 0;
	scanf("%d", &n);
	if (n<55 && n>0)
	{
		printf("%d"nainiu(n));
	}
	else
	{
		return error;
	}
			
			;
}
int nainiu(int n)
{
	if (n <= 4)
	{
		return n;
	}
	else
	{
		return nainiu(n - 1) + nainiu(n - 4) + 1;
	}
}
#include<stdio.h>
int main()
{
	int n = 0;
	scanf("d", &n);
	int num = 0;
	if (n>55 && n<0)
	{
		printf("Error!\n");
	}
	else
	{
		num = muniu(n);
		printf("%d\n", num);
	}
	return 0;
}
int muniu(int n)
{
	if (n <= 4)
	{
		return n;
	}
	else
	{
		return muniu(n - 1) + muniu(n - 4) + 1;
	}
}