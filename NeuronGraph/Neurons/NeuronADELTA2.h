#pragma once
#include "Neuron.h"
//2��matrix�Ĳ�Ķ��׷�����x��
class NeuronADELTA2 :
	public Neuron
{
	
	//ʵ����������Ϊcnt
	//���ֻ��Ϊ1��double
public:
	double x;	//����ϵ��
	NeuronADELTA2();
	void run();
	void bp();
	void init();
	~NeuronADELTA2();
};

