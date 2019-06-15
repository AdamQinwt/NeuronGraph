#pragma once
#include"Neurons/NeuronADD.h"
#include"Neurons/NeuronADELTA2.h"
#include"Neurons/NeuronAL2.h"
#include"Neurons/NeuronConstant.h"
#include"Neurons/NeuronFC.h"
#include"Neurons/NeuronCONV.h"
#include"Neurons/NeuronMAXPOOL.h"
#include"Neurons/NeuronVariable.h"
class NeuronGraph
{
public:
	//basic info
	Neuron* in;
	Neuron* out;
	Neuron* ans;
	Neuron* loss;

	int trainableCnt;
	Trainable** trainables;	//trainables table
	int* trainablesIndx;	//indexes of trainables

	int count;	//number of neurons in the graph
	Neuron** sequence;	//a topological sequencing of neurons

	void run();
	void bp();
	void reset();
	void resetGrad();
	NeuronGraph();
	NeuronGraph(int _count);
	~NeuronGraph();
	//set how many extra matrices are needed for each trainable matrix after the optimizer is selected
	void SetTrainables(const int c);
	//re-sort neurons based on topological sequencing
	void GetSquence();
	void SaveArgsBin(const char* name);
	void ReadArgsBin(const char* name);
	void SaveArgsTxt(const char* name);
	void ReadArgsTxt(const char* name);
};

