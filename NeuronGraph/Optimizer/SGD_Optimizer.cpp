#include "SGD_Optimizer.h"

void SGD_Optimizer::run()
{
	int i;
	register Trainable* p;
	for (i = 0; i < g->trainableCnt; i++)
	{
		p = g->trainables[i];
		p->m[OPT_DELTA].xcopy(p->m[OPT_GRAD], -learningRate / g->sequence[g->trainablesIndx[i]]->nbp);
		p->m[OPT_ORIG].inc(p->m[OPT_DELTA]);
		p->m[OPT_GRAD].Reset();
		g->sequence[g->trainablesIndx[i]]->nbp = 0;
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
