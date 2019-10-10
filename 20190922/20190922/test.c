#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
//void BiSai(int A, int B, int C, int D, int E)
//{
//	for (A = 1; A <= 5; ++A)
//	{
//		for (B = 1; B <= 5; ++B)
//		{
//			for (C = 1; C <= 5; ++C)
//			{
//				for (D = 1; D <= 5; ++D)
//				{
//					for (E = 1; E <= 5; ++E)
//					{		
//						if ((B == 2) + (A == 3) == 1 &&
//							(B == 2) + (E == 4) == 1 &&
//							(C == 1) + (D == 2) == 1 &&
//							(C == 5) + (D == 3) == 1 &&
//							(E == 4) + (A == 1) == 1)
//						{
//							if (A*B*C*D*E == 120)
//							{
//								printf("A是第%d名\n", A);
//								printf("B是第%d名\n", B);
//								printf("C是第%d名\n", C);
//								printf("D是第%d名\n", D);
//								printf("E是第%d名\n", E);
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//}
//
//int main()
//{
//	int A = 0;
//	int B = 0;
//	int C = 0;
//	int D = 0;
//	int E = 0;
//	BiSai(A, B, C, D, E);
//	return 0;
//}
//void MouSha(int a, int b, int c, int d)
//{
//	int i = 0; int f = 0;
//	for (i = 1; i < 5; i++)
//	{
//		if (i == 1)
//		{
//			a = 1; c = 1; f = 1; d = 0;
//		}
//		if (i == 2)
//		{
//			a = 0; c = 0; f = 1; d = 0;
//		}
//		if (i == 3)
//		{
//			a = 0; c = 1; f = 0; d = 0;
//		}
//		if (i == 4)
//		{
//			a = 0; c = 1; f = 1; d = 0;
//		}
//		if ((a + b + c + d + f == 1) && (f == d))
//		{
//			printf(" A=%d\n B=%d\n C=%d\n D=%d\n", a, b, c, d);
//		}
//	}
//}
//int main()
//{
//	int a = 0; int b = 0; int c = 0; int d = 0; 
//	MouSha(a, b, c, d);
//	return 0;
//}
//void YangAngle(int arr[][10], int row, int col)
//{
//	int i = 0;
//	int j = 0;
//	for (i = 0; i < row; i++)
//	{
//		for (j = 0; j <= i; j++)
//		{
//			if (j==0 || i==j)
//			{
//				arr[i][j] = 1;
//			}
//			else
//			{
//				arr[i][j] = arr[i - 1][j] + arr[i - 1][j - 1];
//			}
//		}
//	}
//}
//void show(int arr[][10], int row, int col)
//{
//	int i = 0;
//	int j = 0;
//	for (i = 0; i < row; i++)
//	{
//		for (j = 0; j <= i; j++)
//		{
//			printf("  %-3d ",arr[i][j]);
//		}
//		printf("\n");
//	}
//}
//int main()
//{
//	int arr[10][10] = { 0 };
//	YangAngle(arr, 10, 10);
//	show(arr, 10, 10);
//	return 0;
//}
//#include<math.h>
//unsigned int Reverse_bit(unsigned int value)
//{
//	int i = 0;
//	unsigned int sum = 0;
//	for (i = 0; i < 32; i++)
//	{
//		sum+= ((value >> i) & 1)*pow(2, 31 - i);
//	}
//	return sum;
//}
//int main()
//{
//	int value = 25;
//	unsigned int ret = Reverse_bit(value);
//	printf("ret=%u\n", ret);
//	return 0;
//}
//void ChuFa(int a, int b)
//{
//	int c = 0;
//	c = (a + b) >> 1;
//	printf("%d", c);
//}
//int main()
//{
//	int a = 0; int b = 0;
//	printf("请输入两个整数：");
//	scanf("%d %d", &a, &b);
//	ChuFa(a, b);
//	return 0;
//}
//int Zhaoshuzi( const char arr[], int len)
//{
//	int i = 0;
//	for (int i = 1; i < len; i++)
//	{
//		arr[0] = arr[0] ^ arr[i];
//	}
//	printf("%d\n", arr[0]);
//	return 0;
//}
//int main()
//{
//	char arr[10] = { 1, 5, 4, 9, 5, 2, 1, 6, 4, 7 };
//	 int len = sizeof(arr) / sizeof(arr[0]);
//	int ret= Zhaoshuzi(arr[10], len);
//	printf("%d\n", ret);
//	 return 0;
//}

#include<assert.h>

static int my_strlen(const char *str)
{
	int count = 0;
	while (*str)
	{
		count++;
		str++;
	}
	return count;
}
static void reverse_arr(char *left, char *right)
{
	while (left < right)
	{
		char temp = *right;
		*right = *left;
		*left = temp;
		left++;
		right--;
	}
}
void reverse(char *str)
{
	assert(str != NULL);
	char *left = str;
	char *right = str + my_strlen(str) - 1;
	char *cur = str;
	reverse_arr(left, right);
	while (*cur)
	{
		char *start = cur;
		while ((*cur != ' ') && (*cur != '\0'))
		{
			cur++;
		}

		reverse_arr(start, cur - 1);
		if (*cur == ' ')
		{
			cur++;
		}
	}
}

int main()
{
	char arr[] = "student a am i";
	reverse(arr);
	printf("%s\n", arr);
	return 0;
}

