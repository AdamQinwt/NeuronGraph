#include "NeuronAL2.h"

NeuronAL2::NeuronAL2()
{
	ready = 0;
	ty = AL2;
	isTrain = 0;
	isVarInput = 1;
	capacity = initCap;
	in = new Matrix*[NeuronAL2::initCap];
	din = new Matrix*[NeuronAL2::initCap];
	cnt = 0;
	out = new Matrix(1,1);
	dout = new Matrix(1,1);
}

NeuronAL2::~NeuronAL2()
{
}

void NeuronAL2::run()
{
	double sum = 0;
	for (int i = 0; i < cnt; i++)
	{
		sum += x[i]*(in[i]->L2());
	}
	out->Reset(sum);
}
void NeuronAL2::bp()
{
	for (int i = 0; i < cnt; i++)
	{
		in[i]->DL2(*(in[i]),dout->data[0], x[i]);
	}
}
void NeuronAL2::init()
{
	//ÎÞ²Ù×÷
}