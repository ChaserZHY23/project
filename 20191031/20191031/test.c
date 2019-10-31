#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
//struct S1
//{
//	char c1;
//	int i;
//	char c2;
//};
//struct S2
//{
//	char c1;
//	char c2;
//	int i;
//};
//int main()
//{
//	printf("%d\n", sizeof(struct S1));
//	printf("%d\n", sizeof(struct S2));
//}
struct S3{
	double d;
	char c;
	int i;
};
 struct S4 
 { char c1;
 struct S3 s3;
 double d;
 };
 int main()
 {
	 printf("%d\n", sizeof(struct S3));
	 printf("%d\n", sizeof(struct S4));
 }

