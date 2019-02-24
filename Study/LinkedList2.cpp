#include <iostream>

using namespace std;

#define MAX_SIZE 100

typedef struct Information
{
	int grade;

	Information(int num = 0) : grade(num) {};
}INFO, *pINFO;


typedef struct Node
{
	INFO Info;
	Node* next;
	Node* prev;

	Node(int num = 0) : Info(num) {};
}Node, *pNode;

typedef struct List
{
	pNode Begin;
	pNode End;
	int size;
}List, *pList;

void InitList(pList list)
{
	list->size = 0;
	
	list->Begin = new Node;
	list->End = new Node;

	list->Begin->next = list->End;
	list->End->prev = list->Begin;
	list->Begin->prev = NULL;
	list->End->next = NULL;
}

void destroy(pList list)
{
	pNode n = list->Begin;

	while (n != NULL)
	{
		pNode nextN = n->next;
		delete n;
		n = nextN;
	}
}
pNode getEntry(List list, int num)
{
	pNode n = list.Begin;
	for (int i = -1; i < num; i++, n = n->next)
		if (n == NULL) break;
	return n;
}

void insert(List list, int num, pNode n)
{
	pNode prevN = getEntry(list, num - 1);
	if (prevN != NULL)
	{
		if (prevN->next != NULL)
			prevN->next->prev = n;
		prevN->next = n;
		n->prev = prevN;
		n->next = prevN->next;
		list.size++;
	}
}

void remove(List list, int num)
{
	pNode delNode = getEntry(list, num);
	if (delNode != NULL)
	{
		delNode->next->prev = delNode->prev;
		delNode->prev->next = delNode->next;
		list.size--;
	}
}

void main()
{
	List list;
	Node n(2);

	InitList(&list);

	insert(list, 0, &n);

	cout << list.Begin->Info.grade << endl;
	cout << list.Begin->next->Info.grade << endl;
	cout << list.size << endl;

	//destroy(&list);

	getchar();
	getchar();
}