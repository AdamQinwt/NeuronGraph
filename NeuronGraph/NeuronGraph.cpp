#include "NeuronGraph.h"

void NeuronGraph::run()
{
	for (int i = 0; i < count; i++)
	{
		sequence[i]->run();
	}
}
void NeuronGraph::bp()
{
	for (int i = count-1; i>=0; i--)
	{
		sequence[i]->bp();
	}
}
void NeuronGraph::reset()
{
	for (int i = 0; i < count; i++)
	{
		sequence[i]->reset();
	}
}

void NeuronGraph::resetGrad()
{
	for (int i = 0; i < count; i++)
	{
		sequence[i]->resetGrad();
	}
}

NeuronGraph::NeuronGraph()
{
}
NeuronGraph::NeuronGraph(int _count):count(_count)
{
	sequence = new Neuron*[count];
}

NeuronGraph::~NeuronGraph()
{
	//delete all neurons
	for (int i = 0; i < count; i++)
	{
		delete sequence[i];
	}
	delete[] sequence;
}
void NeuronGraph::SetTrainables(const int c)	//在设置optimizer后，设置图中的可训练数据的多余存储个数
{
	for (int i = 0; i < count; i++)
	{
		if (sequence[i]->ty == VARIABLE) sequence[i]->arg.cnt = c;
	}
}
void NeuronGraph::GetSquence()	//在所有定义和连接完成后，计算拓扑排序
{
	//
}