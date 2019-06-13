#include "RMSProp_Optimizer.h"

void RMSProp_Optimizer::run()
{
	int i;
	for (i = 0; i < g->count; i++)
	{
		if (g->sequence[i]->isTrain)
		{
			g->sequence[i]->arg.m[OPT_GRAD].mul(1 / (double)g->sequence[i]->nbp);
			g->sequence[i]->arg.m[OPT_ACC_SQR_GRAD].kinc2(ro, 1 - ro, g->sequence[i]->arg.m[OPT_GRAD]);
			g->sequence[i]->arg.m[OPT_DELTA].divideAndSqrt2(-learningRate, _delta, g->sequence[i]->arg.m[OPT_ACC_SQR_GRAD], g->sequence[i]->arg.m[OPT_GRAD]);
			g->sequence[i]->arg.m[OPT_ORIG].inc(g->sequence[i]->arg.m[OPT_DELTA]);
			g->sequence[i]->arg.m[OPT_GRAD].Reset();
			g->sequence[i]->nbp = 0;
		}
	}
}

RMSProp_Optimizer::RMSProp_Optimizer(NeuronGraph* _g,double _learningRate, double _ro, double _del):learningRate(_learningRate),ro(_ro),_delta(_del)
{
	g = _g;
	trainableCount = 4;
	g->SetTrainables(trainableCount);
}


RMSProp_Optimizer::~RMSProp_Optimizer()
{
}
