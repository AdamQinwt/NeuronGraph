#pragma once
#include "Neuron.h"

class NeuronADD :
	public Neuron
{
	const static int initCap = 10;
	double* x;	//��in��Ӧ�ķ���ϵ��
	//ʵ����������Ϊcnt
	int capacity;	//����
	//���ֻ��Ϊ1��double
public:
	NeuronADD();
	void run();
	void bp();
	void init();
	~NeuronADD();
};

