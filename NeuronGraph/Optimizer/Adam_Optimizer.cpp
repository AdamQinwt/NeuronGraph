#include "Adam_Optimizer.h"

void Adam_Optimizer::run()
{
	int i;
	for (i = 0; i < g->count; i++)
	{
		if (g->sequence[i]->isTrain)
		{
			g->sequence[i]->arg.m[OPT_GRAD].mul(1 / (double)g->sequence[i]->nbp);
			g->sequence[i]->arg.m[OPT_DELTA].getAdamDelta(g->sequence[i]->arg.m[OPT_G1], g->sequence[i]->arg.m[OPT_G2], g->sequence[i]->arg.m[OPT_GRAD], _ro1, _ro2, ro1, ro2, _step, _delta);
			g->sequence[i]->arg.m[OPT_ORIG].inc(g->sequence[i]->arg.m[OPT_DELTA]);
			g->sequence[i]->arg.m[OPT_GRAD].Reset();
			g->sequence[i]->nbp = 0;
			ro1 *= _ro1;
			ro2 *= _ro2;
		}
	}
}

Adam_Optimizer::Adam_Optimizer(NeuronGraph* _g, double step, double delta, double r1, double r2):_step(step),_delta(delta),_ro1(r1),_ro2(r2),ro1(r1),ro2(r2)
{
	g = _g;
	trainableCount = 5;
	g->SetTrainables(trainableCount);
}


Adam_Optimizer::~Adam_Optimizer()
{
}
