#pragma once
#include "Neuron.h"
#define FC_IN 0
#define FC_W 1
#define FC_B 2
class NeuronAL2 :
	public Neuron
{
	const static int initCap = 10;
	double* x;	//与in对应的范数系数
	//实际连接数量为cnt
	int capacity;	//容量
	//输出只能为1个double
public:
	NeuronAL2();
	void run();
	void bp();
	void init();
	~NeuronAL2();
};

