#pragma once
#include "Neuron.h"
#define FC_IN 0
#define FC_W 1
#define FC_B 2
class NeuronAL2 :
	public Neuron
{
	const static int initCap = 10;
	double* x;	//��in��Ӧ�ķ���ϵ��
	//ʵ����������Ϊcnt
	int capacity;	//����
	//���ֻ��Ϊ1��double
public:
	NeuronAL2();
	void run();
	void bp();
	void init();
	~NeuronAL2();
};

