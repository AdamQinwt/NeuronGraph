#pragma once
#include"Neurons/NeuronADD.h"
#include"Neurons/NeuronADELTA2.h"
#include"Neurons/NeuronAL2.h"
#include"Neurons/NeuronConstant.h"
#include"Neurons/NeuronFC.h"
#include"Neurons/NeuronCONV.h"
#include"Neurons/NeuronMAXPOOL.h"
#include"Neurons/NeuronVariable.h"
#include"Neurons/NeuronCrossEntropy.h"
#include"SeqSet.h"
class NeuronGraph
{
public:
	//basic info
	Neuron* in;
	Neuron* out;
	Neuron* ans;
	Neuron* loss;

	//the table of trainables is set in SetTrainables
	int trainableCnt;
	Trainable** trainables;	//trainables table
	int* trainablesIndx;	//indexes of trainables

	//how many copies(of space) of trainables are needed
	int NeedTrainables;

	int count;	//number of neurons in the graph
	Neuron** sequence;	//the array of neurons
	int indx;	//currrent index in sequence, can be used for any purpose
	vector<SeqSet*> seqSets;

	void run();
	void bp();
	void reset();
	void resetGrad();
	NeuronGraph(int _count=5);
	~NeuronGraph();
	//Set the trainables table in the graph
	void SetTrainables();
	//re-sort neurons based on topological sequencing
	void GetSquence();
	//append a neuron to the graph
	void AppendNeuron(Neuron* n);

	//Functions to efficiently add Neurons to the graph
	Neuron* AddFC(Neuron* x, int cntIn,int cntOut,const char* activate);
	Neuron* AddConv(Neuron* x, int il,int ih,int iw,int ol, int oh, int ow, int kh, int kw, int ph, int pw, int sh, int sw, const char* activate);
	Neuron* AddMaxPool(Neuron* x, int il, int ih, int iw, int ol,int oh, int ow, int kh, int kw, int ph, int pw, int sh, int sw);
	//y is the answer and x is the output. The output is xx*||x-y||
	Neuron* AddADelta2(Neuron* x, Neuron* y, int xx = 1);
	//y is the answer and x is the output. The output is CE(x,y)
	Neuron* AddCrossEntropy(Neuron* x, Neuron* y);

	//functions to save and read arguments
	void SaveArgsBin(const char* name);
	void ReadArgsBin(const char* name);
	void SaveArgsTxt(const char* name);
	void ReadArgsTxt(const char* name);
};

