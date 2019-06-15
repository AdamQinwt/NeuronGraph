#include "Adam_Optimizer.h"

void Adam_Optimizer::run()
{
	int i;
	register Trainable* p;
	for (i = 0; i < g->trainableCnt; i++)
	{
		p = g->trainables[i];
		p->m[OPT_GRAD].mul(1 / (double)g->sequence[g->trainablesIndx[i]]->nbp);
		p->m[OPT_DELTA].getAdamDelta(p->m[OPT_G1], p->m[OPT_G2], p->m[OPT_GRAD], _ro1, _ro2, ro1, ro2, _step, _delta);
		p->m[OPT_ORIG].inc(p->m[OPT_DELTA]);
		p->m[OPT_GRAD].Reset();
		g->sequence[g->trainablesIndx[i]]->nbp = 0;
		ro1 *= _ro1;
		ro2 *= _ro2;
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
