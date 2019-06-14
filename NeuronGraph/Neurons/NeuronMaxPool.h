#pragma once
#include "Neuron.h"

class NeuronMaxPool :
	public Neuron
{
	pointPair*** p;
	int*** maxIndx;
	int fw, fh;
	int pw, ph;
	int sw, sh;
	int il, ih, iw;
	int ol, oh, ow;
	int ksize;
public:
	NeuronMaxPool(int _fw, int _fh, int _pw, int _ph, int _sw, int _sh, int _il, int _ih, int _iw, int _ol, int _oh, int _ow);
	void run();
	void bp();
	void init();
	~NeuronMaxPool();
};

