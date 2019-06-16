#include"Dataset.h"
#include"Normalized_Initializer.h"
#include"Optimizer\SGD_Optimizer.h"
#include"Optimizer\AdaGrad_Optimizer.h"
#include"Optimizer\RMSProp_Optimizer.h"
#include"Optimizer\Adam_Optimizer.h"
#include"Optimizer\ConjGrad_Optimizer.h"
#include"Optimizer\ConjGradImproved_Optimizer.h"
void train(Optimizer* opt,Dataset* d,NeuronGraph* g,int times=100,double thresh=0.01)
{
	int iter;
	double loss;
	d->fromFile();
	d->Init();
	for (iter = 0; iter < times; iter++)
	{
		//reset 
		loss=d->DoBatch();
		printf("After %d iterations, the loss is %lf.\n", iter, loss);
		if (loss < thresh)
		{
			puts("Success!");
			break;
		}
		opt->run();
	}
	d->disConnect();
}
int main()
{
	/*Order
	1.NeuronGraph
	2.Dataset
	3.Optimizer
	4.Neurons in the NeuronGraph
	5.Initialize dataset with FromFile()
	5.Initialize arguments with an initializer or from a file
	*/

	//1 
	NeuronGraph* g = new NeuronGraph();

	//2
	Dataset d("xor.txt",g);
	d.SetIn(1, 2);
	d.SetOut(1, 1);
	
	//3
	//SGD_Optimizer opt(g,0.3,0);
	//AdaGrad_Optimizer opt(g);
	//RMSProp_Optimizer opt(g);
	//Adam_Optimizer opt(g);
	ConjGradImproved_Optimizer opt(g, &d);

	//4
	Neuron* tmp;
	g->in = new NeuronConst(1, 2);
	g->ans = new NeuronConst(1, 1);
	g->AppendNeuron(g->in);
	g->AppendNeuron(g->ans);
	tmp = g->AddFC(g->in, 2,3, "sigmoid");
	tmp = g->AddFC(tmp, 3,1, "sigmoid");
	g->out = tmp;
	tmp = g->AddADelta2(tmp, g->ans);
	g->loss = tmp;

	g->SetTrainables();
	g->GetSquence();

	//5
	d.FromFile();
	Normalized_Initializer init(g,3);
	init.run();
	//g->ReadArgsBin("args");
	//g->ReadArgsTxt("args.txt");

	train(&opt, &d, g,100000,0.001);
	d.TestBatch();

	d.disConnect();
	//g->SaveArgsBin("args");
	g->SaveArgsTxt("args.txt");
	delete g;
	PS;
}