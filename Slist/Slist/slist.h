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
SListNode* BuySListNode(SLDataType x);//����һ���µĽڵ�
void SListPrint(SListNode*plist);//��ӡ������
void SListPushBack(SListNode**pplist, SLDataType x);//β�巨
void SListPushFront(SListNode**pplist, SLDataType x);//β��ͷ�巨
void SListPopBack(SListNode**pplist);//βɾ��
void SListPopFront(SListNode**pplist);//βͷɾ��
