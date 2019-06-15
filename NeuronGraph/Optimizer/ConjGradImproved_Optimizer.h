#pragma once
#include "Optimizer.h"
#include"../Dataset.h"
class ConjGradImproved_Optimizer :
	public Optimizer
{
	const double tol;	//min{a-b}
	const double tau1;	//\tau1
	const double tau2;	//\tau_2=1-\tau_1
	const double expand;	//pace to expand b while L(a)>L(b)
	const double maxExpand;	//max pace to expand b while L(a)>L(b)
	double current_Expand;
	const static int OPT_LAST_G = 3;
	const static int OPT_DIRECTION = 2;
	const static int OPT_A = 4;	//arg_a
	const static int OPT_B = 5;	//arg_b
	const static int OPT_C = 6;	//arg_c
	const static int OPT_D = 7;	//arg_d
	double lossA, lossB, lossC, lossD;
	double expandA, expandB, expandC, expandD;
	Dataset* dataset;
public:
	void run();
	//tau1 should be greater than 0.5
	ConjGradImproved_Optimizer(NeuronGraph* _g,Dataset* _data,double _tol=1e-3, double _tau1=0.618,double _expand=2,double _maxExpand=26);
	~ConjGradImproved_Optimizer();
};

