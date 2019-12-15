#include"slist.h"
SListNode* BuySListNode(SLDataType x)//创造一个新的节点
{
	SListNode *Node = (SListNode*)melloc(sizeof(SListNode));
	Node->data = x;
	Node->next = NULL;
	return Node;
}
void SListPrint(SListNode*plist)//打印单链表
{
	SListNode*cur = plist;
	while (cur != NULL)
	{
		printf("%d->", cur->data);
		cur = cur->next;
	}
	printf("NULL\n");
}
void SListPushBack(SListNode**pplist, SLDataType x)//尾插法
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
void SListPushFront(SListNode**pplist, SLDataType x)//头插法
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
void SListPopBack(SListNode**pplist)//尾删法
{   //考虑节点为空或者只有一个节点
	//考虑两个以上的节点
	//尾删时不仅要删除最后一个，还要找到前一个节点，让前一个节点指针指向空
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
void SListPopFront(SListNode**pplist)//头删法
{
	//考虑没有节点
	//考虑只有一个节点
	//考虑两个及以上的节点
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