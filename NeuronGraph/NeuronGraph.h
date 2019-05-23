#pragma once
#include"Neurons/NeuronADD.h"
#include"Neurons/NeuronADELTA2.h"
#include"Neurons/NeuronAL2.h"
#include"Neurons/NeuronConstant.h"
#include"Neurons/NeuronFC.h"
#include"Neurons/NeuronVariable.h"
class NeuronGraph
{
public:
	//basic info
	Neuron* in;
	Neuron* out;
	Neuron* ans;
	Neuron* loss;
	
	int count;	//����ڵ������
	Neuron** sequence;	//����ͼ����������

	void run();
	void bp();
	void reset();
	void resetGrad();
	NeuronGraph();
	NeuronGraph(int _count);
	~NeuronGraph();
	void SetTrainables(const int c);	//������optimizer������ͼ�еĿ�ѵ�����ݵĶ���洢����
	void GetSquence();	//�����ж����������ɺ󣬼�����������
};

