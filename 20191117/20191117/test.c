#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<windows.h>
int total(int size)
{
	if (size == 0)
	{
		return 1;
	}
	return 10 * total(size - 1);
}
int main()
{
	int num = 0;
	int i = 1;
	int size = 0;
	int n = 0;
	int in[10] = { 0 };
	int sum = 0;
	scanf("%d", &num);
	n = num;
	while (1)
	{
		in[size] = n % 10;
		size++;
		n = n / 10;
		if (n == 0)
		{
			break;
		}
	}
	n = 1;
	while (i != size)
	{
		while (in[i] != 0)
		{
			if (in[i] == 2)
			{
				sum = sum + total(i);
			}
			else
			{
				sum += n;
			}
			in[i]--;
		}
		n = n * 9 + total(i);
		i++;
	}
	if (in[0] >= 2)
	{
		sum++;
	}
	sum = num - sum;
	printf("%d", sum);
	system("pause");
	return 0;
}
	
//#include<stdio.h>
//int main()
//{
//	char a[100];
//	int i; int n = 0;
//	scanf("%s", a);
//	for (i = 0; i<100; ++i)
//	{
//		if (a[i] == '\0')
//		{
//			printf("n");
//			return 0;
//		}
//		while(a[i] == 'a' || a[i] == 'e' || a[i] == 'i' || a[i] == 'o' || a[i] == 'u')
//		{
//				printf("%c", a[i]);
//				return 0;
//		}
//	}
//	return 0;
//}
//int main()
//{
//	char a[100];
//	int i; int n = 0;
//	scanf("%s", a);
//	for (i = 0; i<100; ++i)
//	{
//		while (a[i] == 'a' || a[i] == 'e' || a[i] == 'i' || a[i] == 'o' || a[i] == 'u')
//		{
//			printf("%c", a[i]);
//			return 0;
//		}
//	}
//	printf("n");
//	return 0;
//}
//#include<stdio.h>
//int main()
//{
//	int n;
//	scanf("%d", &n);
//	int a, b, c;
//	scanf("%d %d %d", &a, &b, &c);
//	int i = 0;
//	int count = 0;
//	for (i = 0; i < n;++i)
//	{
//		if (i%a != 0 && i%b != 0 && i%c != 0)
//		{
//			count++;
//		}
//	}
//	printf("%d", count);
//	return 0;
//}
//#include<stdio.h>
//int main()
//{
//	char a[100];
//	char b[100];
//	int i; int n = 0;
//	scanf("s", &a);
//	for (i = 0; i<100; ++i)
//	{
//		if (a[i] == 'a' || a[i] == 'e' || a[i] == 'i' || a[i] == 'o' || a[i] == 'u')
//		{
//			b[i] = a[i];
//			printf("%s", b[0]);
//		}
//		else
//		{
//			return n;
//		}
//	}
//	return 0;
//}