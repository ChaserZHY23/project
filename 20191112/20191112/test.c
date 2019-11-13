#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include<assert.h>
#include<string.h>
#include<stbdio.h>
void rotate_left( char* str, int k)
{
	assert(str);
	int len = strlen(str);
	reverse_str(str, str + k - 1);
	reverse_str(str + kreverse_str(str, str + k - 1) :, str + len - 1);
	reverse_str(str, str + len - 1);
	/*while (k--)
	{
		char tmp = *str;
		char *cur = str;
		while (*(cur + 1) != '\0')
		{
			*cur = *(cur + 1);
			++cur;
		}
		*cur = tmp;
	}*/
}
void resverse_str(char*left, char*right)
{
	while (left < right)
	{
		char tmp = *left;
		*left = *right;
		*right = tmp;
		++left;
		--right;
	}
}
int main()
{
	char a[] = "asdfg";
	printf("%s\n", a);
	rotate_left(a, 2);
	printf("%s\n", a);
	return 0;
}
int is_rotate(char*str, char*rt_str)
{
	int len = strlen(str);
	char*double_str = (char*)malloc(len * 2 + 1);
	strcpy(double_str, str);
	strcat(double_str, str);
	if (strstr(double_str, rt_str) != NULL)
	{
		free(double_str);
		return 1;
	}
	else
	{
		free(double_str);
		return 0;
	}
}
int main()
{
	int a[]=
}