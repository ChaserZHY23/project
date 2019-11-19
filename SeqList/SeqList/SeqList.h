//#pragma once
#ifndef __SEQLIST_H__
#define __SEQLIST_H__
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
typedef int SLDataType;
typedef struct Seqlist
{
	SLDataType* _a;
	size_t _size;
	size_t _capacity;
}SeqList;
void SeqListInit(SeqList *ps);//��ʼ��
void SeqListDestory(SeqList *ps);//�Կռ���ͷ�
void SeqListPrint(SeqList *ps);//��ӡ
void SeqListCheckCapacity(SeqList *ps);//�Կռ��������
void SeqListPushBack(SeqList *ps, SLDataType x);//β�巨
void SeqListPopBack(SeqList *ps);//βɾ��
void SeqListPushFront(SeqList *ps, SLDataType x);//ͷ�巨
void SeqListPopFront(SeqList *ps);//ͷɾ��
int SeqListFind(SeqList *ps, SLDataType x);//����������±�
void SeqListInsert(SeqList *ps, size_t pos, SLDataType x);//������λ�ò���Ԫ��
void SeqListErase(SeqList *ps, size_t pos);//������λ��ɾ��Ԫ��
void SeqListRemove(SeqList *ps, SLDataType x);//����X�Լ���
#endif
 