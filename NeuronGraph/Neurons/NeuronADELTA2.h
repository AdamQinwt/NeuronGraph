#pragma once
#include "Neuron.h"
//2个matrix的差的二阶范数的x倍
class NeuronADELTA2 :
	public Neuron
{
	
	//实际连接数量为cnt
	//输出只能为1个double
public:
	double x;	//范数系数
	NeuronADELTA2();
	void run();
	void bp();
	void init();
	~NeuronADELTA2();
};

