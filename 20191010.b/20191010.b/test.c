#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
void Batton(int* arr, int len)
{
	int i = 0; int flg = 0;
	for (i = 0; i < len - 1; i++)//ÌËÊý
	{
		int j = 0; int tmp = 0; flg = 0;
		for (j = 0; i < len - 1 - i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
				flg = 1;
			}
		}
		if (!flg)
		{
			break;
		}
	}
}

void Show(int* arr,int len)
	{
		int i = 0;
		for (i = 0; i < len; i++)
		{
			printf("%d ", arr[i]);
		}
		printf("\n");
	}
	int main()
	{
		int arr[] = { 4, 9, 5, 2, 4, 5, 3, 78, 43, 67 };
		int len = sizeof(arr) / sizeof(arr[0]);
		Show(arr, len);
		Batton(arr, len);
		Show(arr, len);
	}
	

//#include<stdio.h>
//void Batton(int* arr[10], int len)
//{
//	int i = 0; int flg = 0;
//	for (i = 0; i < len - 1; i++)//ÌËÊý
//	{
//		int j = 0; 
//		int tmp = 0; 
//		flg = 0;
//		for (j = 0; i < len - 1 - i; j++)
//		{
//			if (arr[j] > arr[j + 1])
//			{
//				tmp = arr[j];
//				arr[j] = arr[j + 1];
//				arr[j + 1] = tmp;
//				flg = 1;
//			}
//		}
//		if (!flg)
//		{
//			break;
//		}
//	}
//}
//
//void Show(int* arr[10], int len)
//{
//	int i = 0;
//	for (i = 0; i < len; i++)
//	{
//		printf("%d\n", arr[i]);
//	}
//	printf("\n");
//}
//int main()
//{
//	int arr[] = { 4, 9, 5, 2, 4, 5, 3, 78, 43, 67 };
//	int len = sizeof(arr) / sizeof(arr[0]);
//	Show(arr[10], len);
//	Batton(arr[10], len);
//	Show(arr[10], len);
//}
//
