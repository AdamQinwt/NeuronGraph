#include "Trainable.h"



Trainable::Trainable()
{
}


Trainable::~Trainable()
{
	delete[] m;
	delete[] dims;
}
void Trainable::Alloc()	//分配空间
{
	m = new Matrix[cnt];
	for (int i = 0; i < cnt; i++)
	{
		m[i].Set(dim, dims);
		m[i].alloc();
		m[i].Reset();
	}
}
void Trainable::Set(const int _dim, const int* _dims)	//需要复制
{
	dim = _dim;
	dims = new int[dim];
	memcpy(dims, _dims, dim * sizeof(int));
}