#pragma once
#include"NeuronGraph.h"
class Dataset
{
	FILE* fp;
	void calcInfo();	//count已知时，计算batch, batchSize, remainder
public:
	int dimIn,dimOut;
	int* dimsIn,*dimsOut;
	NeuronGraph * g;
	Matrix* din,*loss;
	Matrix** x, **ans;
	int batch, batchSize, count, remainder;
	int indx;

	Dataset(const char* fname,NeuronGraph* _g);
	//run and bp
	double DoBatch();
	//only the forward calculations and returns the total loss
	double ForwardBatch();
	//only the forward calculations and prints the output
	void TestBatch();
	void SetIn(int _dim, ...);
	void SetOut(int _dim, ...);
	//read data into the given space
	void fromFile();
	//only allocs space
	void FromFile();
	//put data into the input and answers in the NeuronGraph
	void putData();
	//alloc space for the NeuronGraph that is not allocated in Connect
	void Init();
	//disConnect dataset and NeuronGraph
	void disConnect();
	~Dataset();
};

