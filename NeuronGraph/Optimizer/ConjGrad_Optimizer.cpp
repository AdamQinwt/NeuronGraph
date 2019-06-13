#include "ConjGrad_Optimizer.h"

void ConjGrad_Optimizer::run()
{
	int i,n;
	for (n = 0; n < SEARCH; n++)
	{
		g->reset();
		g->resetGrad();

	}
	for (i = 0; i < g->count; i++)
	{
		if (g->sequence[i]->isTrain)
		{
			g->sequence[i]->arg.m[OPT_GRAD].mul(1 / (double)g->sequence[i]->nbp);
			g->sequence[i]->arg.m[OPT_ORIG].inc(g->sequence[i]->arg.m[OPT_DELTA]);
			g->sequence[i]->arg.m[OPT_GRAD].Reset();
			g->sequence[i]->nbp = 0;
		}
	}
}

ConjGrad_Optimizer::ConjGrad_Optimizer(NeuronGraph* _g, int search, double _step):SEARCH(search),step(_step)
{
	g = _g;
	trainableCount = 7;
	g->SetTrainables(trainableCount);
}


ConjGrad_Optimizer::~ConjGrad_Optimizer()
{
}
