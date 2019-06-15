#include "NeuronConstant.h"

void NeuronConst::run()
{
	//�޲���
	//����һ������������ֱ�������Լ���������
	next[0]->in[indxAsOut] = out;
}
void NeuronConst::bp()
{
	//�޲���
}
void NeuronConst::init()
{
	//�޲���
	//out = in[0];
	//dout = din[0];
}

NeuronConst::NeuronConst(const int _dim, ...)
{
	ready = 1;
	isTrain = 0;
	isVarInput = 0;
	capacity = 0;
	ty = CONSTANT;
	in = nullptr;
	cnt = 0;
	va_list ap;
	va_start(ap, _dim);
	int* dims= new int[_dim];
	for (int i = 0; i < _dim; i++)
		dims[i] = va_arg(ap, int);
	va_end(ap);
	dout = new Matrix(_dim, dims);
	delete[] dims;
}


NeuronConst::~NeuronConst()
{
}
