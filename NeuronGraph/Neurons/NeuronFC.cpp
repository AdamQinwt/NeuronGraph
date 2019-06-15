#include "NeuronFC.h"

NeuronFC::NeuronFC(int _in, int _out,const char* activate):nin(_in),nout(_out)
{
	ready = 0;
	ty=FC;
	//设置激活函数
	if (!strcmp(activate, "sigmoid"))
	{
		act = sigmoid;
		dact = dsigmoid;
	}
	else if (!strcmp(activate, "relu"))
	{
		act = relu;
		dact = drelu;
	}
	else if (!strcmp(activate, "tanh"))
	{
		act = nntanh;
		dact = dnntanh;
	}
	else
	{
		act = none;
		dact = none;
	}
	isTrain = 0;
	isVarInput = 0;
	capacity = 3;
	in = new Matrix*[3];
	din = new Matrix*[3];
	cnt = 0;
	in[FC_IN]=new Matrix(1, nin);
	din[FC_IN]=new Matrix(1, nin);
	in[FC_W]=new Matrix(1, nin);
	din[FC_W]=new Matrix(1, nin);
	in[FC_B]=new Matrix(1, nin);
	din[FC_B]=new Matrix(1, nin);
	out = new Matrix(1, nout);
	dout = new Matrix(1, nout);
}

NeuronFC::~NeuronFC()
{
}

void NeuronFC::run()
{
	out->matmulTrans(*(in[FC_IN]), *(in[FC_W]), *(in[FC_B]), act);
}
void NeuronFC::bp()
{
	dout->DmatmulTrans(*(in[FC_IN]),*(in[FC_W]), *(din[FC_IN]), *(din[FC_W]),*(din[FC_B]),*out,dact);
}
void NeuronFC::init()
{
	//无操作
}