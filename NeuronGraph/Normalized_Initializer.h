#pragma once
#include"NeuronGraph.h"
class Normalized_Initializer
{
	NeuronGraph* g;
	double r;
public:
	void run();
	Normalized_Initializer(NeuronGraph* _g, int total);
	~Normalized_Initializer();
};

