#define _CRT_SECURE_NO_WARNINGS 1
#include"SeqList.h"
void SeqListInit(SeqList* ps)
{
	assert(ps);
	ps->_a = NULL;
	ps->_size = 0;
	ps->_capacity = 0;
}
void SeqListDestory(SeqList *ps)
{
	assert(ps);
	free(ps->_a);
	ps->_a = NULL;
	ps->_capacity = ps->_size = 0;
}
void SeqListPushBack(SeqList *ps, SLDataType x)//β�巨
{
	assert(ps);
	SeqListCheckCapacity(ps);
	ps->_a[ps->_size] = x;
	ps->_size++;
}
void SeqListPopBack(SeqList *ps)//βɾ��
{
	assert(ps&&ps->_size>0);
	//ps->_a[ps->_size - 1] = 0;
	ps->_size--;
}
void SeqListPushFront(SeqList *ps, SLDataType x)//ͷ�巨,�ȴ���ռ䲻�����⣬��Ų������
{
	assert(ps);
	SeqListCheckCapacity(ps);
	int end = ps->_size - 1;
	for (; end >= 0; --end)
	{
		ps->_a[end + 1] = ps->_a[end];
	}
	ps->_a[0] = x;
	ps->_size++;
}
void SeqListPopFront(SeqList *ps)//ͷɾ��
{
	assert(ps&&ps->_size>0);
	for (size_t i = 0; i < ps->_size - 1; ++i)
	{
		ps->_a[i] = ps->_a[i + 1];
	}
	for (size_t i = 1; i < ps->_size; ++i)
	{
		ps->_a[i - 1] = ps->_a[i];
	}
	ps->_size--;
	/*size_t b = ps->_size - 2;
	for (; b>= 0; b--)
	{
		ps->_a[b - 1] = ps->_a[b];
	}
	ps->_size--;*/
}
void SeqListCheckCapacity(SeqList *ps)//�Կռ��������
{
	if (ps->_size >= ps->_capacity)
	{
		size_t newcapacity = ps->_capacity == 0 ? 4 : ps->_capacity * 2;
		ps->_a = realloc(ps->_a, newcapacity * sizeof(SLDataType));
		ps->_capacity = newcapacity;
	}
}
void SeqListPrint(SeqList *ps)//��ӡ
{
	assert(ps);
	for (size_t i = 0; i < ps->_size; ++i)
	{
		printf("%d", ps->_a[i]);
	}
	printf("\n");
}
int SeqListFind(SeqList *ps, SLDataType x)//����������±�
{
	assert(ps);
	for (size_t i = 0; i < ps->_size; ++i)
	{
		if (ps->_a[i] == x)
		{
			return i;
		}
	}
	return -1;
}
void SeqListInsert(SeqList *ps, size_t pos, SLDataType x)//������λ�ò���Ԫ��
{
	assert(ps);
	SeqListCheckCapacity(ps);
	for (size_t i =ps->_size; i > pos; --i)
	{
		ps->_a[ps->_size + 1] = ps->_a[ps->_size];
		ps->_a[pos] = x;
	}
	ps->_size++;
}
void SeqListErase(SeqList *ps, size_t pos)//������λ��ɾ��Ԫ��
{
	assert(ps);
	for (size_t i = pos; i <ps->_size-1; --i)
	{
		ps->_a[i] = ps->_a[i+1];
	}
	ps->_size--;
}
void SeqListRemove(SeqList *ps, SLDataType x)//����X�Լ���
{
	int pos = SeqListFind(ps, x);
	if (SeqListFind)(ps, x)
	{
		SeqListErase(ps, pos);
	}
}
