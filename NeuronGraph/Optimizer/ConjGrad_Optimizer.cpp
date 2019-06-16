#include "ConjGrad_Optimizer.h"

void ConjGrad_Optimizer::run()
{
	int i,n;
	double beta;
	double l2_Gt1=0;	//||g_{t-1}||
	double d=0;	//(g_t-g_{t-1})^T g_t
	double loss;
	double bestLoss;

	for (i = 0; i < g->count; i++)
	{
		if (g->sequence[i]->isTrain)
		{
			//get beta
			l2_Gt1 += g->sequence[i]->arg.m[OPT_LAST_G].L2();
			d += Matrix::ConjGrad1(g->sequence[i]->arg.m[OPT_GRAD], g->sequence[i]->arg.m[OPT_LAST_G]);
		}
	}
	beta = l2_Gt1 ?d / l2_Gt1 :0;

	//init before search
	for (i = 0; i < g->count; i++)
	{
		if (g->sequence[i]->isTrain)
		{
			g->sequence[i]->arg.m[OPT_DIRECTION].kinck(step,beta, -1, g->sequence[i]->arg.m[OPT_GRAD]);
			g->sequence[i]->arg.m[OPT_LAST_G].copy(g->sequence[i]->arg.m[OPT_GRAD]);
		}
	}
	bestLoss = INT_MAX;

	for (n = 0; n < SEARCH; n++)
	{
		//try args
		for (i = 0; i < g->count; i++)
		{
			if (g->sequence[i]->isTrain)
			{
				g->sequence[i]->arg.m[OPT_ORIG].inc(g->sequence[i]->arg.m[OPT_DIRECTION]);
			}
		}

		//get loss
		loss=data->ForwardBatch();

		//if better, record
		if (loss < bestLoss)
		{
			bestLoss = loss;
			for (i = 0; i < g->count; i++)
			{
				if (g->sequence[i]->isTrain)
				{
					g->sequence[i]->arg.m[OPT_BEST].copy(g->sequence[i]->arg.m[OPT_ORIG]);
				}
			}
			n--;
		}
	}
	
	//update
	for (i = 0; i < g->count; i++)
	{
		if (g->sequence[i]->isTrain)
		{
			g->sequence[i]->arg.m[OPT_ORIG].copy(g->sequence[i]->arg.m[OPT_BEST]);
		}
	}
}

ConjGrad_Optimizer::ConjGrad_Optimizer(NeuronGraph* _g, Dataset* _data, int search, double _step):SEARCH(search),step(_step),data(_data)
{
	g = _g;
	trainableCount = 6;
	g->NeedTrainables=trainableCount;
}


ConjGrad_Optimizer::~ConjGrad_Optimizer()
{
}
