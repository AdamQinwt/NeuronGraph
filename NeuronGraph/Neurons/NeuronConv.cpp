#include "NeuronConv.h"

NeuronConv::NeuronConv(int _fw, int _fh, int _pw, int _ph, int _sw, int _sh, int _il, int _ih, int _iw, int _ol, int _oh, int _ow, const char* activate):fh(_fh),fw(_fw),ph(_ph),pw(_pw),sw(_sw),sh(_sh),il(_il), ih(_ih), iw(_iw), ol(_ol), oh(_oh), ow(_ow)
{
	ready = 0;
	ty = CONV;
	int i, j, k;
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
	in[CONV_IN] = new Matrix(3,il,ih,iw );
	din[CONV_IN] = new Matrix(3, il, ih, iw);
	in[CONV_K] = new Matrix(4, ol,il,fh,fw);
	din[CONV_K] = new Matrix(4, ol, il, fh, fw);
	in[CONV_B] = new Matrix(1, ol);
	din[CONV_B] = new Matrix(1, ol);
	out = new Matrix(3, ol, oh, ow);
	dout = new Matrix(3, ol, oh, ow);
	ksize = fh * fw;

	int i0, j0, m, n;
	
	//calculate all point pairs
	p = new pointPair**[oh];
	for (i = 0,i0=-ph; i < oh; i++)
	{
		p[i] = new pointPair*[ow];
		for (j = 0,j0=-pw; j < ow; j++)
		{
			p[i][j] = new pointPair[ksize];
			k = 0;
			for (m = 0; m < fh; m++)
			{
				if (i0 + m < 0) continue;
				if (i0 + m >= ih) break;
				for (n = 0; n < fw; n++)
				{
					if (j0 + n < 0) continue;
					if (j0 + n >= iw) break;
					p[i][j][k].ax = i0 + m;
					p[i][j][k].ay = j0 + n;
					p[i][j][k].bx = m;
					p[i][j][k].by = n;
					k++;
				}
			}
			if (k < ksize - 1) p[i][j][k].ax = -1;
			j0 += sw;
		}
		i0 += sh;
	}
}

NeuronConv::~NeuronConv()
{
	//destroy point pairs
	int i, j;
	for (i = 0; i < oh; i++)
	{
		for (j = 0; j < ow; j++)
		{
			delete[] p[i][j];
		}
		delete[] p[i];
	}
	delete[] p;
}

void NeuronConv::run()
{
	out->conv(*(in[CONV_IN]), *(in[CONV_K]), *(in[CONV_B]), p, ksize, act);
}
void NeuronConv::bp()
{
	dout->dconv(*(in[CONV_IN]), *(in[CONV_K]), *(in[CONV_B]), *(din[CONV_IN]), *(din[CONV_K]), *(din[CONV_B]), p, ksize, dact);
}
void NeuronConv::init()
{
	//无操作
}