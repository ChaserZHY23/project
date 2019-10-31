#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
//int main()
//{
//	int a[10] = { 1 };
//	printf("%p\n",a);
//	printf("%p\n", &a[0]);
//	return 0;
//}
//int main()
//{
//	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
//	int*p = arr;
//	int len = sizeof(arr) / sizeof(arr[0]); 
//	int i = 0;
//	for (i = 0; i < len; i++)
//	{
//		printf("&arr[%d]=%p == == == == == == == == p + %d = %p\n", i, &arr[i], i, p + i);
//	}
//		return 0;
//}
int main()
{
	int arr[10] = { 0 };
	printf("arr=%p\n", arr);
	printf("&arr=%p\n", &arr);
	printf("arr+1=%p\n", arr + 1);
	printf("&arr+1=%p\n", &arr + 1);
	return 0;
}