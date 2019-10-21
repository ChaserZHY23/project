#define _CRT_SECURE_NO_WARNINGS 1
void Batton(int*arr, int len)
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

	void Show(int *arr, int len)
	{
		int i = 0;
		for (i = 0; i < len; i++)
		{
			printf("%d\n", arr[i]);
		}
		printf("\n")
	}
	int main()
