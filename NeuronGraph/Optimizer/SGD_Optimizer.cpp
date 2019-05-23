#include "SGD_Optimizer.h"

void SGD_Optimizer::run()
{
	int i;
	for (i = 0; i < g->count; i++)
	{
		if (g->sequence[i]->isTrain)
		{
			//Matrix::add(g->sequence[i]->arg.m[OPT_DELTA], g->sequence[i]->arg.m[OPT_DELTA], g->sequence[i]->arg.m[OPT_GRAD],momentum,)
			g->sequence[i]->arg.m[OPT_DELTA].inc(g->sequence[i]->arg.m[OPT_GRAD], -learningRate/g->sequence[i]->nbp);
			g->sequence[i]->arg.m[OPT_ORIG].inc(g->sequence[i]->arg.m[OPT_DELTA]);
			g->sequence[i]->arg.m[OPT_GRAD].Reset();
			g->sequence[i]->nbp = 0;
		}
	}
}

SGD_Optimizer::SGD_Optimizer(NeuronGraph* _g,double _learningRate, double _momentum):learningRate(_learningRate),momentum(_momentum)
{
	g = _g;
	trainableCount = 3;
	g->SetTrainables(trainableCount);
}


SGD_Optimizer::~SGD_Optimizer()
{
}
