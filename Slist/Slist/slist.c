#include"slist.h"
SListNode* BuySListNode(SLDataType x)//����һ���µĽڵ�
{
	SListNode *Node = (SListNode*)melloc(sizeof(SListNode));
	Node->data = x;
	Node->next = NULL;
	return Node;
}
void SListPrint(SListNode*plist)//��ӡ������
{
	SListNode*cur = plist;
	while (cur != NULL)
	{
		printf("%d->", cur->data);
		cur = cur->next;
	}
	printf("NULL\n");
}
void SListPushBack(SListNode**pplist, SLDataType x)//β�巨
{
	SListNode*newNode = BuySListNode(x);
	if (*pplist == NULL)
	{
		*pplist = newNode;
	}
	else
	{
		SListNode*tail = *pplist;
		while (tail ->next= NULL)
		{
			tail = tail->next;
		}
		tail->next = newNode;
	}
}
void SListPushFront(SListNode**pplist, SLDataType x)//ͷ�巨
{
	SListNode*newNode = BuySListNode(x);
	if (pplist == NULL)
	{
		*pplist = newNode;
	}
	else
	{
		newNode->next = *pplist;
		*pplist = newNode;
	}
}
void SListPopBack(SListNode**pplist)//βɾ��
{   //���ǽڵ�Ϊ�ջ���ֻ��һ���ڵ�
	//�����������ϵĽڵ�
	//βɾʱ����Ҫɾ�����һ������Ҫ�ҵ�ǰһ���ڵ㣬��ǰһ���ڵ�ָ��ָ���
	SListNode*tail = *pplist;
	SListNode*prev = NULL;
	if (tail ==NULL || tail->next == NULL)
	{
		free(tail);
		*pplist = NULL;
	}
	else
	{
		while (tail->next != NULL)
		{
			prev = tail;
			tail = tail->next;
		}
		free(tail);
		tail = NULL;
		prev->next = NULL;
	}
}
void SListPopFront(SListNode**pplist)//ͷɾ��
{
	//����û�нڵ�
	//����ֻ��һ���ڵ�
	//�������������ϵĽڵ�
	SListNode*tail = *pplist;
	if (tail == NULL)
	{
		return;
	}
	else if (tail->next == NULL)
	{
		free(tail);
		*pplist = NULL;
	}
	else
	{
		SListNode*next = tail->next;
		free(tail);
		*pplist = next;
	}
}