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
	delete[] trainables;
	delete[] trainablesIndx;
}
void NeuronGraph::SetTrainables(const int c)	//在设置optimizer后，设置图中的可训练数据的多余存储个数
{
	trainables = new Trainable*[count];
	trainablesIndx = new int[count];
	for (int i = 0; i < count; i++)
	{
		if (sequence[i]->ty == VARIABLE)
		{
			trainablesIndx[trainableCnt] = i;
			trainables[trainableCnt++] = &sequence[i]->arg;
			sequence[i]->arg.cnt = c;
		}
	}
}
void NeuronGraph::GetSquence()
{
	//TODO
}
void NeuronGraph::SaveArgsBin(const char* name)
{
	FILE* fp = fopen(name, "wb");
	for (int i = 0; i < trainableCnt; i++)
	{
		trainables[i]->m[ORIG].WriteBin(fp);
	}
	fclose(fp);
}
void NeuronGraph::ReadArgsBin(const char* name)
{
	FILE* fp = fopen(name, "rb");
	for (int i = 0; i < trainableCnt; i++)
	{
		trainables[i]->m[ORIG].ReadBin(fp);
	}
	fclose(fp);
}
void NeuronGraph::SaveArgsTxt(const char* name)
{
	FILE* fp = fopen(name, "w");
	for (int i = 0; i < trainableCnt; i++)
	{
		trainables[i]->m[ORIG].WriteTxt(fp);
	}
	fclose(fp);
}
void NeuronGraph::ReadArgsTxt(const char* name)
{
	FILE* fp = fopen(name, "r");
	for (int i = 0; i < trainableCnt; i++)
	{
		trainables[i]->m[ORIG].ReadTxt(fp);
	}
	fclose(fp);
}