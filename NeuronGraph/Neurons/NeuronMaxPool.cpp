#include "NeuronMaxPool.h"

NeuronMaxPool::NeuronMaxPool(int _fw, int _fh, int _pw, int _ph, int _sw, int _sh, int _il, int _ih, int _iw, int _ol, int _oh, int _ow) :fh(_fh), fw(_fw), ph(_ph), pw(_pw), sw(_sw), sh(_sh), il(_il), ih(_ih), iw(_iw), ol(_ol), oh(_oh), ow(_ow)
{
	ready = 0;
	ty = MAX_POOL;
	int i, j, k;
	isTrain = 0;
	isVarInput = 0;
	capacity = 1;
	in = new Matrix*[1];
	din = new Matrix*[1];
	cnt = 0;
	in[0] = new Matrix(3, il, ih, iw);
	din[0] = new Matrix(3, il, ih, iw);
	out = new Matrix(3, ol, oh, ow);
	dout = new Matrix(3, ol, oh, ow);
	ksize = fh * fw;

	int i0, j0, m, n;

	//calculate all point pairs
	p = new pointPair**[oh];
	maxIndx = new int**[oh];
	for (i = 0, i0 = -ph; i < oh; i++)
	{
		p[i] = new pointPair*[ow];
		maxIndx[i] = new int*[ow];
		for (j = 0, j0 = -pw; j < ow; j++)
		{
			p[i][j] = new pointPair[ksize];
			maxIndx[i][j] = new int[ol];
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
					//p[i][j][k].bx = m;
					//p[i][j][k].by = n;
					k++;
				}
			}
			if (k < ksize - 1) p[i][j][k].ax = -1;
			j0 += sw;
		}
		i0 += sh;
	}
}
NeuronMaxPool::~NeuronMaxPool()
{
	//destroy point pairs
	int i, j;
	for (i = 0; i < oh; i++)
	{
		for (j = 0; j < ow; j++)
		{
			delete[] p[i][j];
			delete[] maxIndx[i][j];
		}
		delete[] maxIndx[i];
		delete[] p[i];
	}
	delete[] maxIndx;
	delete[] p;
}
void NeuronMaxPool::run()
{
	out->maxPool(*(in[0]), p, maxIndx, ksize);
}
void NeuronMaxPool::bp()
{
	dout->dmaxPool(*(din[0]), p, maxIndx);
}
void NeuronMaxPool::init()
{
	//ÎÞ²Ù×÷
}