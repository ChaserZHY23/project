#include"AddressBook.h"
void AdderssBookInit(AddressBook*pbook)
{
	assert(pbook);
	pbook->_size = 0;
	pbook->_capacity = 2;
	pbook->_AIArrray = (AddressInfo*)malloc(sizeof(AddressInfo) * 2);
	assert(pbook->_AIArrray);
}
void AddressBookAdd(AddressBook* pbook, AddressInfo* pinfo)
{
	assert(pbook);
	if (pbook->_size == pbook->_capacity)//空间已满，进行扩容
	{
		pbook->_AIArrray = realloc(pbook->_AIArrray, pbook->_capacity * 2 * sizeof(AddressInfo));
		pbook->_capacity *= 2;
	}
	strcpy(pbook->_AIArrray[pbook->_size]._name, pinfo->_name);
	strcpy(pbook->_AIArrray[pbook->_size]._tell, pinfo->_tell);
	pbook->_AIArrray[pbook->_size]._age = pinfo->_age;
	pbook->_AIArrray[pbook->_size]._sex = pinfo->_sex;
	pbook->_size++;
}
void AddressBookDel(AddressBook*pbook, const char*name)
{

}
void AddressbookSave(AddressBook*pbook, const char*filename)
{
	assert(pbook);
	FILE*fp = fopen(filename, "w");
	for (size_t i = 0; i < pbook->_size; ++i)
	{
		fwrite(&(pbook->_AIArrray[i]), sizeof(AddressInfo), 1,fp);
	}
	AddressInfo end;
	end._age = -1;
	fwrite(&end, sizeof(AddressInfo), 1, fp);
}
void AddressBookLoad(AddressBook* pbook, const char* filename)
{
	assert(pbook);
	FILE* fp = fopen(filename, "r");
	AddressInfo info;

	while (1)
	{
		fread(&info, sizeof(AddressInfo), 1, fp);
		if (info._age == -1)
		{
			break;
		}
		else
		{
			AddressBookAdd(pbook, &info);
		}
	}
}
AddressInfo* AddressBookFind(AddressBook* pbook, const char* name)
{
	return NULL;
}
void AddressBookPrint(AddressBook* pbook)
{
	assert(pbook);

	for (size_t i = 0; i < pbook->_size; ++i)
	{
		//printf("======================================\n");
		printf("name:%s\n", pbook->_AIArrray[i]._name);
		printf("tel:%s\n", pbook->_AIArrray[i]._tell);
		printf("age:%d\n", pbook->_AIArrray[i]._age);
		printf("sex:%d\n", pbook->_AIArrray[i]._sex);
		//printf("======================================\n");
		printf("\n");

	}
}