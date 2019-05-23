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
	
	int count;	//计算节点的数量
	Neuron** sequence;	//计算图的拓扑排序

	void run();
	void bp();
	void reset();
	void resetGrad();
	NeuronGraph();
	NeuronGraph(int _count);
	~NeuronGraph();
	void SetTrainables(const int c);	//在设置optimizer后，设置图中的可训练数据的多余存储个数
	void GetSquence();	//在所有定义和连接完成后，计算拓扑排序
};

