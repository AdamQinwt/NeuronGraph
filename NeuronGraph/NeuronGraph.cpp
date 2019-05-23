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
void NeuronGraph::SetTrainables(const int c)	//������optimizer������ͼ�еĿ�ѵ�����ݵĶ���洢����
{
	for (int i = 0; i < count; i++)
	{
		if (sequence[i]->ty == VARIABLE) sequence[i]->arg.cnt = c;
	}
}
void NeuronGraph::GetSquence()	//�����ж����������ɺ󣬼�����������
{
	//
}