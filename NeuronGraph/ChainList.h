#pragma once
template<class T>
class ChainNode
{
public:
	T data;
	ChainNode* next;
	ChainNode(const T _data)
	{
		data = _data;
		next = nullptr;
	}
};
template<class T>
class ChainList
{
public:
	ChainNode<T>* head;
	ChainNode<T>* tail;
	ChainList();
	~ChainList();
	void Append(const T _data);
};

