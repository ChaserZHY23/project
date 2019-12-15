#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
typedef int SLDataType;
typedef struct SListNode
{
	SLDataType data;
	struct SListNode* next;
}SListNode;
SListNode* BuySListNode(SLDataType x);//创造一个新的节点
void SListPrint(SListNode*plist);//打印单链表
void SListPushBack(SListNode**pplist, SLDataType x);//尾插法
void SListPushFront(SListNode**pplist, SLDataType x);//尾、头插法
void SListPopBack(SListNode**pplist);//尾删法
void SListPopFront(SListNode**pplist);//尾头删法
