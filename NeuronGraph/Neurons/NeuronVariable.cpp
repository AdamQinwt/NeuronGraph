#include "NeuronVariable.h"

void NeuronVariable::run()
{
	//�޲���
}
void NeuronVariable::bp()
{
	//�޲���
	nbp++;
}
void NeuronVariable::init()
{
	//�޲���
}

NeuronVariable::NeuronVariable(const int _dim, ...)
{
	ready = 1;
	isTrain = 1;
	isVarInput = 0;
	capacity = 0;
	ty = VARIABLE;
	in = nullptr;
	out = nullptr;
	cnt = 0;
	va_list ap;
	va_start(ap, _dim);
	int* dims= new int[_dim];
	for (int i = 0; i < _dim; i++)
		dims[i] = va_arg(ap, int);
	va_end(ap);
	arg.Set(_dim,dims);
	delete[] dims;
}


NeuronVariable::~NeuronVariable()
{
}
