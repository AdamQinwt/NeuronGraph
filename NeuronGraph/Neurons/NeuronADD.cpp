#include "NeuronADD.h"

NeuronADD::NeuronADD()
{
	ready = 0;
	ty = ADD;
	isTrain = 0;
	isVarInput = 1;
	capacity = initCap;
	in = new Matrix*[NeuronADD::initCap];
	din = new Matrix*[NeuronADD::initCap];
	cnt = 0;
	out = new Matrix();
	dout = new Matrix();
}

NeuronADD::~NeuronADD()
{
}

void NeuronADD::run()
{
	out->copy(*(in[0]));
	for (int i = 1; i < cnt; i++)
	{
		out->inc(*(in[i]));
	}
}
void NeuronADD::bp()
{
	for (int i = 0; i < cnt; i++)
	{
		din[i]->inc(*dout);
	}
}
void NeuronADD::init()
{
	//ÎÞ²Ù×÷
}