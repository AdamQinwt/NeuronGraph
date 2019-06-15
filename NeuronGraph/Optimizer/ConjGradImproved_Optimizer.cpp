#include "ConjGradImproved_Optimizer.h"

void ConjGradImproved_Optimizer::run()
{
	int i;
	double beta;
	double l2_Gt1 = 0;	//||g_{t-1}||
	double d = 0;	//(g_t-g_{t-1})^T g_t
	register Trainable* p;
	for (i = 0; i < g->trainableCnt; i++)
	{
			p = g->trainables[i];
			//get beta
			l2_Gt1 += p->m[OPT_LAST_G].L2();
			//d += Matrix::ConjGrad1(p->m[OPT_GRAD], p->m[OPT_LAST_G]);
			d+= p->m[OPT_GRAD].L2();
	}
	beta = l2_Gt1 ? d / l2_Gt1 : 0;

	//init before search
	lossA = dataset->ForwardBatch();//g->loss->out->data[0];
	current_Expand = expand;
	for (i = 0; i < g->trainableCnt; i++)
	{
		p = g->trainables[i];
		//if (g->sequence[i]->nbp > 1) p->m[OPT_GRAD].mul(((double)1) / ((double)(g->sequence[i]->nbp)));
		p->m[OPT_DIRECTION].kinc(beta, -1, p->m[OPT_GRAD]);
		p->m[OPT_LAST_G].copy(p->m[OPT_GRAD]);
		p->m[OPT_GRAD].Reset();
		p->m[OPT_A].copy(p->m[OPT_ORIG]);
		p->m[OPT_ORIG].inck(current_Expand, p->m[OPT_DIRECTION]);
	}
	lossB = dataset->ForwardBatch();

	while (lossA > lossB)
	{
		current_Expand *= expand;
		for (i = 0; i < g->trainableCnt; i++)
		{
			p = g->trainables[i];
			Matrix::add(p->m[OPT_ORIG], p->m[OPT_A], p->m[OPT_DIRECTION], 1, current_Expand);
		}
		lossB = dataset->ForwardBatch();
		if (current_Expand > maxExpand) break;
	}

	//copy args to B
	for (i = 0; i < g->trainableCnt; i++)
	{
		p = g->trainables[i];
		p->m[OPT_B].copy(p->m[OPT_ORIG]);
	}

	//printf("Expand=%.1lf\n", current_Expand);
	expandA = 0;
	expandB = current_Expand;

	//calculate C,D
	//C
	for (i = 0; i < g->trainableCnt; i++)
	{
		p = g->trainables[i];
		Matrix::add(p->m[OPT_ORIG], p->m[OPT_A], p->m[OPT_B], tau1, tau2);
		p->m[OPT_C].copy(p->m[OPT_ORIG]);
		expandC = average(expandA, tau1, expandB, tau2);
	}
	lossC = dataset->ForwardBatch();

	//D
	for (i = 0; i < g->trainableCnt; i++)
	{
		p = g->trainables[i];
		Matrix::add(p->m[OPT_ORIG], p->m[OPT_A], p->m[OPT_B], tau2, tau1);
		p->m[OPT_D].copy(p->m[OPT_ORIG]);
		expandD = average(expandA, tau2, expandB, tau1);
	}
	lossD = dataset->ForwardBatch();

loop_search:
	//printf("ExpandC=%lf\tExpandD=%lf\n", expandC, expandD);
	//printf("LossC=%lf\tLossD=%lf\n", lossC, lossD);
	if (expandD - expandC < tol) goto end_loop;

	if (lossC < lossD)
	{
		expandB = expandD;	//b=d
		expandD = expandC;	//d=c
		lossB = lossD;
		lossD = lossC;

		//update C
		for (i = 0; i < g->trainableCnt; i++)
		{
			p = g->trainables[i];
			p->m[OPT_B].copy(p->m[OPT_D]);
			p->m[OPT_D].copy(p->m[OPT_C]);
			Matrix::add(p->m[OPT_ORIG], p->m[OPT_A], p->m[OPT_B], tau1, tau2);
			p->m[OPT_C].copy(p->m[OPT_ORIG]);
			expandC = average(expandA, tau1, expandB, tau2);
		}
		lossC = dataset->ForwardBatch();
	}
	else
	{
		expandA = expandC;	//a=c
		expandC = expandD;	//c=d
		lossA = lossC;
		lossC = lossD;

		//update D
		for (i = 0; i < g->trainableCnt; i++)
		{
			p = g->trainables[i];
			p->m[OPT_A].copy(p->m[OPT_C]);
			p->m[OPT_C].copy(p->m[OPT_D]);
			Matrix::add(p->m[OPT_ORIG], p->m[OPT_A], p->m[OPT_B], tau2, tau1);
			p->m[OPT_D].copy(p->m[OPT_ORIG]);
			expandD = average(expandA, tau2, expandB, tau1);
		}
		lossD = dataset->ForwardBatch();
	}

	goto loop_search;
end_loop:
	//compare a,b,c and use the best
	if (lossA <= lossB&&lossA <= lossC)
	{
		//puts("Still use A.");
		for (i = 0; i < g->trainableCnt; i++)
		{
			p = g->trainables[i];
			p->m[OPT_ORIG].copy(p->m[OPT_A]);
		}
	}
	else if (lossB < lossA&&lossB < lossC)
	{
		//puts("Still use B.");
		for (i = 0; i < g->trainableCnt; i++)
		{
			p = g->trainables[i];
			p->m[OPT_ORIG].copy(p->m[OPT_B]);
		}
	}
}

ConjGradImproved_Optimizer::ConjGradImproved_Optimizer(NeuronGraph* _g, Dataset* _data, double _tol, double _tau1, double _expand, double _maxExpand):tol(_tol),tau1(_tau1),tau2(1-_tau1),expand(_expand),maxExpand(_maxExpand),current_Expand(0),dataset(_data),lossA(0), lossB(0), lossC(0), lossD(0)
{
	g = _g;
	trainableCount = 8;
	g->SetTrainables(trainableCount);
}


ConjGradImproved_Optimizer::~ConjGradImproved_Optimizer()
{
}
