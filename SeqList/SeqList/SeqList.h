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
void SeqListInit(SeqList *ps);//初始化
void SeqListDestory(SeqList *ps);//对空间的释放
void SeqListPrint(SeqList *ps);//打印
void SeqListCheckCapacity(SeqList *ps);//对空间进行扩容
void SeqListPushBack(SeqList *ps, SLDataType x);//尾插法
void SeqListPopBack(SeqList *ps);//尾删法
void SeqListPushFront(SeqList *ps, SLDataType x);//头插法
void SeqListPopFront(SeqList *ps);//头删法
int SeqListFind(SeqList *ps, SLDataType x);//返回数组的下标
void SeqListInsert(SeqList *ps, size_t pos, SLDataType x);//在任意位置插入元素
void SeqListErase(SeqList *ps, size_t pos);//在任意位置删除元素
void SeqListRemove(SeqList *ps, SLDataType x);//给定X自己找
#endif
 