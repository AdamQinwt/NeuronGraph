#pragma once
#include<vector>
#include"Matrix.h"
using namespace std;
class Neuron
{
protected:
	enum {CONSTANT,VARIABLE,ADD,AXPB,CONV,MAX_POOL,AX,AX2} type;
	int cnt;	//how many matrices are there
	Matrix* in;
	Matrix* out;
	vector<Neuron*> prev, next;
public:
	Neuron();
	virtual void init()=0;
	virtual void run()=0;
	virtual void bp()=0;
	static void connect(Neuron& n1,int i1,Neuron& n2,int i2);
	~Neuron();
};

