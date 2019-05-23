#pragma once
#include "Neuron.h"

class NeuronADD :
	public Neuron
{
	const static int initCap = 10;
	double* x;	//与in对应的范数系数
	//实际连接数量为cnt
	int capacity;	//容量
	//输出只能为1个double
public:
	NeuronADD();
	void run();
	void bp();
	void init();
	~NeuronADD();
};

