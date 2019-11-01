#define _CRT_SECURE_NO_WARNINGS 1
//#include<stdio.h>
//static int j;
//void fun1(void)
//{
//	static int i=0;
//	i++;
//}
//void fun2(void)
//{
//	j = 0;
//	j++;
//}
//int main()
//{
//	int k = 0;
//	for (k = 0; k < 10; k++)
//	{
//		fun1();
//		fun2();
//	}
//	return 0;
//}
#include<stdio.h>
//int main()
//{
//	int k = 0;
//	for (k = 'A', k <= 'D', k++)
//	{
//		if ((k != 'A') + (k == 'C') + (k == 'D') + (k != 'D') == 3)
//		{
//			printf("k=%c\n", k);
//			return 0;
//		}
//	}
//	return 1;
//}
//int main()
//{
//	int k = 0;
//	for (k = 'A'; k <= 'D'; k++)
//	{
//		if ((k != 'A') + (k == 'C') + (k == 'D') + (k != 'D') == 3)
//		{
//			printf("k=%c\n", k);
//			return 0;
//		}
//	}
//	return 1;
//}
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int main()
{
int k;
printf("请输入一个数：");
scanf("%d", &k);
int n;
int a[10] = { 0 };
int i;
int sum = 0;
int count = 0;
for (n = 0; n < k;++n)
{
	for (i = n; i; i = i / 10)
	{
		a[count] = i % 10;
		++count;
	}
	for (i = 0; i < count; ++i)
	{
		sum += pow(a[i], count);
	}
	if (n == sum)
	{
		printf("%d \n", n);
	}
	count = sum = 0;
}
return 0;
}
int main()
{
	int a = 1;
	int b = a++;
	int c= ++a;
	
	printf("%d %d", b, c);
	return 0;
}