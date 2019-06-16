#pragma once
#include "Neuron.h"

class NeuronConv :
	public Neuron
{
	pointPair*** p;
	int fw, fh;
	int pw, ph;
	int sw, sh;
	int il, ih, iw;
	int ol, oh, ow;
	int ksize;
	double(*act)(double);
	double(*dact)(double);
public:
	const static int CONV_IN = 0;
	const static int CONV_K = 1;
	const static int CONV_B = 2;
	NeuronConv(int _fw,int _fh,int _pw,int _ph,int _sw,int _sh,int _il,int _ih,int _iw,int _ol,int _oh,int _ow,const char* activate);
	void run();
	void bp();
	void init();
	~NeuronConv();
};

