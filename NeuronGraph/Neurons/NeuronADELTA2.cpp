#include "NeuronADELTA2.h"

NeuronADELTA2::NeuronADELTA2():x(1)
{
	ty = ADELTA2;
	isTrain = 0;
	isVarInput = 0;
	capacity = 2;
	in = new Matrix*[2];
	din = new Matrix*[2];
	cnt = 0;
	out = new Matrix(1, 1);
	dout = new Matrix(1, 1);
}

NeuronADELTA2::~NeuronADELTA2()
{
}

void NeuronADELTA2::run()
{
	double sum = in[0]->delta2(*(in[1]),x);
	//sum *= x;
	//out->inc(sum);
	out->Reset(sum);
}
void NeuronADELTA2::bp()
{
	din[0]->Ddelta2(*(in[0]),*(in[1]),dout->data[0],x);
}
void NeuronADELTA2::init()
{
	//ÎÞ²Ù×÷
}