#pragma once
#include "Optimizer.h"
class AdaGrad_Optimizer :
	public Optimizer
{
	double learningRate;
	double momentum;
	const static int OPT_ADAGRAD_ACC_SQR_GRAD = 3;	//�ۼ�ƽ���ݶ�
	const double _delta;
	const double _epsilon;
public:
	void run();
	AdaGrad_Optimizer(NeuronGraph* _g,double _eps=0.3, double _del=1e-7);
	~AdaGrad_Optimizer();
};

