#include "NeuronCrossEntropy.h"

NeuronCrossEntropy::NeuronCrossEntropy()
{
	ready = 0;
	ty = CE;
	isTrain = 0;
	isVarInput = 0;
	capacity = 2;
	in = new Matrix*[2];
	din = new Matrix*[2];
	cnt = 0;
	out = new Matrix(1, 1);
	dout = new Matrix(1, 1);
}

NeuronCrossEntropy::~NeuronCrossEntropy()
{
}

void NeuronCrossEntropy::run()
{
	in[0]->clip();
	double sum = in[0]->crossEntropy(*(in[1]));
	out->Reset(sum);
}
void NeuronCrossEntropy::bp()
{
	din[0]->dcrossEntropy(*(in[0]),*(in[1]),dout->data[0]);
}
void NeuronCrossEntropy::init()
{
	//ÎÞ²Ù×÷
}