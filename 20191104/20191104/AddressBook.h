#pragma once
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<string.h>
enum SEX
{
	Man,
	Woman,
};
typedef struct AssressInfo
{
	char _name[24];
	char _tell[24];
	int _age;
	enum SEX _sex;
} AddressInfo;//通讯录基本信息
typedef struct AddressBook
{
	AddressInfo*_AIArrray;
	size_t _size;//数据的个数
	size_t _capacity;//通讯录容量
}AddressBook;
void AddressBookInit(AddressBook*pbook);//初始化通讯录
void AddressBookAdd(AddressBook*pbook, AddressInfo*pinfo);//添加通讯人
void AddressBookDel(AddressBook*pbook, const char*name);//删除通讯人
AddressInfo* AddressBookFind(AddressBook* pbook, const char* name);//寻找通讯人
void AddressBookSave(AddressBook* pbook, const char* filename);//存储通讯人
void AddressBookLoad(AddressBook* pbook, const char* filename);//加载通讯人
void AddressBookPrint(AddressBook* pbook);//打印通讯录