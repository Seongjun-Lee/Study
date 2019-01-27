#include <cstdio>

class Node
{
	Node* prev;
	Node* next;
	int data;
public :
	Node(int val = 0) : data(val), prev(NULL), next(NULL) {}
	Node* getPrev() { return prev; }
	Node* getNext() { return next; }

	void setPrev(Node* p) { prev = p; }
	void setNext(Node* n) { next = n; }
	bool hasData(int val) { return data == val; }

	void insertNext(Node* n)
	{
		if (n != NULL)
		{
			n->prev = this;
			n->next = next;
			if (next != NULL)
				next->prev = n;
			next = n;
		}

	}
	Node* removeNext()
	{
		if (prev != NULL)
			prev->next = next;
		if (next != NULL)
			next->prev = prev;
		return this;
	}
};

class DoubleLinked
{
	Node head;
	int size = 0;
public:
	DoubleLinked() : head(0), size(0) {}
	~DoubleLinked() { while (isEmpty()) delete remove(0); }
	Node* getHead() { return head.getNext(); }
	bool isEmpty() { return getHead() == NULL; }

	Node* getEntry(int num)
	{
		Node* n = &head;
		for (int i = -1; i < num; i++, n = n->getNext())
			if (n == NULL)
				break;
		return n;
	}

	void insert(int num, Node* n)
	{
		Node* prev = getEntry(num - 1);
		if (prev != NULL)
		{
			prev->insertNext(n);
			size++;
		}
	}

	Node* remove(int num)
	{
		Node* n = getEntry(num);
		if (n != NULL)
			size--;
		return n->removeNext();
	}

	Node* find(int val)
	{
		for (Node* p = getHead(); p != NULL; p = p->getNext())
			if (p->hasData(val))
				return p;
		return NULL;
	}

	void replace(int num, Node* n)
	{
		Node* prev = getEntry(num - 1);
		if (prev != NULL)
		{
			delete prev->getNext()->removeNext();
			prev->insertNext(n);
		}
	}

	int size() {
		/*
		int count = 0;
		for (Node* p = getHead(); p != NULL; p = p->getNext())
			count++;
		return count;
		*/
		return size;
	}
};