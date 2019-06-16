#include "NeuronGraph.h"

void NeuronGraph::run()
{
	int i, j;
	for (i = 0; i < seqSets.size(); i++)
	{
		for (j = 0; j < seqSets[i]->v.size(); j++)
		{
			seqSets[i]->v[j]->run();
		}
	}
}
void NeuronGraph::bp()
{
	int i, j;
	for (i= seqSets.size() - 1; i >=0; i--)
	{
		for (j = 0; j < seqSets[i]->v.size(); j++)
		{
			seqSets[i]->v[j]->bp();
		}
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

NeuronGraph::NeuronGraph(int _count):count(_count),indx(0)
{
	sequence = (Neuron**)malloc(count * sizeof(Neuron*));
}

NeuronGraph::~NeuronGraph()
{
	//delete all neurons
	for (int i = 0; i < count; i++)
	{
		delete sequence[i];
	}
	free(sequence);
	for (int i = 0; i < seqSets.size(); i++)
	{
		delete seqSets[i];
	}
	delete[] trainables;
	delete[] trainablesIndx;
}
//Set the trainables table in the graph
void NeuronGraph::SetTrainables()
{
	count = indx;
	trainables = new Trainable*[count];
	trainablesIndx = new int[count];
	for (int i = 0; i < count; i++)
	{
		if (sequence[i]->ty == VARIABLE)
		{
			trainablesIndx[trainableCnt] = i;
			trainables[trainableCnt++] = &sequence[i]->arg;
		}
	}
}
void NeuronGraph::GetSquence()
{
	int i;
	int finished=0;
	seqSets.clear();
	//Trainables and constants can run first
	SeqSet* s = new SeqSet();
	for (i = 0; i < count; i++)
	{
		if (sequence[i]->ready)
		{
			s->v.push_back(sequence[i]);
			finished++;
		}
	}
	seqSets.push_back(s);
	while (finished < count)
	{
		s = new SeqSet(count, sequence,finished);
		seqSets.push_back(s);
	}
}
//append a neuron to the graph
void NeuronGraph::AppendNeuron(Neuron* n)
{
	if (indx == count)
	{
		count <<= 1;
		sequence = (Neuron**)realloc(sequence, count * sizeof(Neuron*));
	}
	sequence[indx++] = n;
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

//Functions to efficiently add Neurons to the graph
Neuron* NeuronGraph::AddFC(Neuron* x, int cntIn,int cntOut, const char* activate)
{
	Neuron* fc = new NeuronFC(cntIn, cntOut, activate);
	Neuron* w = new NeuronVariable(NeedTrainables,2, cntIn, cntOut);
	Neuron* b = new NeuronVariable(NeedTrainables, 1, cntOut);
	Neuron::connect(*x, *fc, FC_IN);
	Neuron::connect(*w, *fc, FC_W);
	Neuron::connect(*b, *fc, FC_B);
	AppendNeuron(w);
	AppendNeuron(b);
	AppendNeuron(fc);
	return fc;
}
Neuron* NeuronGraph::AddConv(Neuron* x, int il, int ih, int iw, int ol, int oh, int ow, int kh, int kw, int ph, int pw, int sh, int sw, const char* activate)
{
	Neuron* conv = new NeuronConv(kw, kh, pw, ph, sw, sh, il, ih, iw, ol, oh, ow, activate);
	Neuron* kernel = new NeuronVariable(NeedTrainables, 4, ol, il, kh, kw);
	Neuron* b = new NeuronVariable(NeedTrainables, 1, ol);
	Neuron::connect(*x, *conv, NeuronConv::CONV_IN);
	Neuron::connect(*kernel, *conv, NeuronConv::CONV_K);
	Neuron::connect(*b, *conv, NeuronConv::CONV_B);
	AppendNeuron(kernel);
	AppendNeuron(b);
	AppendNeuron(conv);

	return conv;
}
Neuron* NeuronGraph::AddMaxPool(Neuron* x, int il, int ih, int iw, int ol,int oh, int ow, int kh, int kw, int ph, int pw, int sh, int sw)
{
	Neuron* pool = new NeuronMaxPool(kw, kh, pw, ph, sw, sh, il, ih, iw, ol, oh, ow);
	Neuron::connect(*x, *pool);
	AppendNeuron(pool);
	return pool;
}
//y is the answer and x is the output. The output is xx*||x-y||
Neuron* NeuronGraph::AddADelta2(Neuron* x, Neuron* y, int xx)
{
	NeuronADELTA2* delta2 = new NeuronADELTA2();
	delta2->x = xx;
	Neuron::connect(*x, *delta2);
	Neuron::connect(*y, *delta2);
	AppendNeuron(delta2);
	return delta2;
}
//y is the answer and x is the output. The output is CE(x,y)
Neuron* NeuronGraph::AddCrossEntropy(Neuron* x, Neuron* y)
{
	Neuron* ce = new NeuronCrossEntropy();
	Neuron::connect(*x, *ce);
	Neuron::connect(*y, *ce);
	AppendNeuron(ce);
	return ce;
}