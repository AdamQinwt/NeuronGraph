#include "ChainList.h"


template<class T>
ChainList<T>::ChainList()
{
	head = nullptr;
	tail = nullptr;
}

template<class T>
ChainList<T>::~ChainList()
{
	if (!head) return;
	ChainNode* tmp;
	while (head->next)
	{
		tmp = head->next;
		delete head;
		head = tmp;
	}
	delete head;
}

template<class T>
void ChainList<T>::Append(const T _data)
{
	if (head)
	{
		tail->next = new ChainNode(_data);
		tail = tail->next;
	}
	else
	{
		head = new ChainNode(_data);
		tail = head;
	}
}