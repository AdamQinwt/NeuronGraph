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
	double DoBatch();
	double ForwardBatch();
	void TestBatch();
	void SetIn(int _dim, ...);
	void SetOut(int _dim, ...);
	void fromFile();
	void FromFile();
	void putData();
	void Init();
	void disConnect();
	~Dataset();
};

