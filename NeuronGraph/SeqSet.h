#pragma once
#include"Neurons/Neuron.h"
using namespace std;
//set of neurons that can be done
class SeqSet
{
public:
	vector<Neuron*> v;
	SeqSet(int count, Neuron** seq,int& finished);
	SeqSet();
	~SeqSet();
};

