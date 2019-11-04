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
} AddressInfo;//ͨѶ¼������Ϣ
typedef struct AddressBook
{
	AddressInfo*_AIArrray;
	size_t _size;//���ݵĸ���
	size_t _capacity;//ͨѶ¼����
}AddressBook;
void AddressBookInit(AddressBook*pbook);//��ʼ��ͨѶ¼
void AddressBookAdd(AddressBook*pbook, AddressInfo*pinfo);//���ͨѶ��
void AddressBookDel(AddressBook*pbook, const char*name);//ɾ��ͨѶ��
AddressInfo* AddressBookFind(AddressBook* pbook, const char* name);//Ѱ��ͨѶ��
void AddressBookSave(AddressBook* pbook, const char* filename);//�洢ͨѶ��
void AddressBookLoad(AddressBook* pbook, const char* filename);//����ͨѶ��
void AddressBookPrint(AddressBook* pbook);//��ӡͨѶ¼