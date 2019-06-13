#include "AdaGrad_Optimizer.h"

void AdaGrad_Optimizer::run()
{
	int i;
	for (i = 0; i < g->count; i++)
	{
		if (g->sequence[i]->isTrain)
		{
			//Matrix::add(g->sequence[i]->arg.m[OPT_DELTA], g->sequence[i]->arg.m[OPT_DELTA], g->sequence[i]->arg.m[OPT_GRAD],momentum,)
			//g->sequence[i]->arg.m[OPT_DELTA].inc(g->sequence[i]->arg.m[OPT_GRAD], -learningRate/g->sequence[i]->nbp);
			g->sequence[i]->arg.m[OPT_GRAD].mul(1 / (double)g->sequence[i]->nbp);
			g->sequence[i]->arg.m[OPT_ADAGRAD_ACC_SQR_GRAD].incSqr(g->sequence[i]->arg.m[OPT_GRAD]);
			g->sequence[i]->arg.m[OPT_DELTA].divideAndSqrt(-_epsilon, _delta, g->sequence[i]->arg.m[OPT_ADAGRAD_ACC_SQR_GRAD], g->sequence[i]->arg.m[OPT_GRAD]);
			g->sequence[i]->arg.m[OPT_ORIG].inc(g->sequence[i]->arg.m[OPT_DELTA]);
			g->sequence[i]->arg.m[OPT_GRAD].Reset();
			g->sequence[i]->nbp = 0;
		}
	}
}

AdaGrad_Optimizer::AdaGrad_Optimizer(NeuronGraph* _g, double _eps, double _del):_epsilon(_eps),_delta(_del)
{
	g = _g;
	trainableCount = 4;
	g->SetTrainables(trainableCount);
}


AdaGrad_Optimizer::~AdaGrad_Optimizer()
{
}
