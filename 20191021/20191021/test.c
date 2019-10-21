#define _CRT_SECURE_NO_WARNINGS 1
//#include<stdio.h>
//#include<string.h>
//
//void Xuanzhuan(char*b,int k)
//{
//	int len = strlen(b);
//	char*p; char*q;
//	for ()
//
//
//}
//int main()
//{
//	char str[10];
//	scanf("%s/", str);
//	int k = 0;
//	printf("输入旋转字符个数：");
//	scanf("%d", &k);
//	if (k > strlen(str))
//	{
//		printf("输入有误");
//	}
//	
//
//	return 0;
//}

#include <stdio.h>
#include <string.h>
			//左旋字符串中的 k 个字符
//void Rotate(char* s, int k) 
//	    {
//			int len = strlen(s);
//			char* p;
//			char* q;
//			for (p = s + k - 1; p >= s; --p) 
//			{
//				for (q = p; q < p + len - k; ++q) 
//				{
//					char tmp = *q;
//					*q = *(q + 1);
//					*(q + 1) = tmp;
//				}
//			}
//		}
//		int main()
//		{
//			char string[10];
//			scanf("%s", string);
//			int k = 0;
//			printf("请输入你要旋转的字符个数:");
//			scanf("%d", &k);
//			if (k > (int)strlen(string)) {
//				printf("输入有误\n");
//			}
//			Rotate(string, k);
//			printf("%s\n", string);
//			return 0;
//		}
//#include <stdio.h>                                                                                                                      
//#include <string.h>    
////左旋 k 个字符    
//void LeftRotate(char* s, int k) {
//	int len = strlen(s);
//	char* p;
//	char* q;
//	for (p = s + k - 1; p >= s; --p) {
//		for (q = p; q < p + len - k; ++q) {
//			char tmp = *q;
//			*q = *(q + 1);
//			*(q + 1) = tmp;
//		}
//	}
//}
////右旋 k 个字符    
//void RightRotate(char* s, int k) {
//	int len = strlen(s);
//	char* p;
//	char* q;
//	for (p = s + len - k; p < s + len; ++p) {
//		for (q = p; q > s; --q) {
//			char tmp = *q;
//			*q = *(q - 1);
//			*(q - 1) = tmp;
//		}
//	}
//}
////判断 s1 是否为 s2 旋转之后的字符串
//int isRotate(char* s1, char* s2) {
//	int len1 = strlen(s1);
//	int len2 = strlen(s2);
//	if (len1 != len2) {
//		return 0;
//	}
//	char* s;
//	int i;
//	for (i = 0; i <= len1; ++i) {
//		s = s1;
//		LeftRotate(s, i);
//		if (strcmp(s, s2) == 0) {
//			return 1;
//		}
//		s = s1;
//		RightRotate(s, i);
//		if (strcmp(s, s2) == 0) {
//			return 1;
//		}
//	}
//	return 0;
//}
//int main() {
//	char s1[] = "AABCD";
//	char s2[] = "BCDAA";
//	if (isRotate(s1, s2) == 1) {
//		printf("是旋转之后的\n");
//	}
//	else {
//		printf("不是旋转之后\n");
//	}
//	return 0;
//}
char* my_strcpy(char*dst, const char*src)
{
	assert(dst&&src);
	while ((*dst++ == *src++));
	return dst;
}
char* my_strcat(char*dst, const char*src)
{
	assert(dst&&src);
	while (*src++);
	while ((*dst++ == *src++));
	return dst;
}
const char* my_strstr(const char*str1, const char*str2)
{
	assert(str1&&str2);
	const char*src = str1;
	const char*sub = str2;
	while (*src)
	{
		const char*start = src;
		while (*src == *sub&&*sub != '/0')
		{
			++src;
			++sub;
		}
		if (*sub == '/0')
		{
			return start;
		}
		else
		{
			src = start + 1;
			sub = str2;
		}
	}
	return NULL;
}