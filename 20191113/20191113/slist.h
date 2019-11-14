#pragma
typedef int SLDateType;
typedef struct SListNode
{
	SLDateType data;
	struct SListNode* next;
}SListNode;
void SListPushBack(SListNode* plist, SLDateType x);