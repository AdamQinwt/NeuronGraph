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
	NeuronGraph* g = new NeuronGraph(9);
	Dataset d("xor.txt",g);
	d.SetIn(1, 2);
	d.SetOut(1, 1);
	g->sequence[0] = new NeuronConst(1,2);
	g->in = g->sequence[0];
	g->sequence[1] = new NeuronVariable(2, 2, 3);
	g->sequence[2] = new NeuronVariable(1, 3);
	g->sequence[3] = new NeuronFC(2,3,"sigmoid");
	
	g->sequence[4] = new NeuronVariable(2, 3, 1);
	g->sequence[5] = new NeuronVariable(1, 1);
	g->sequence[6] = new NeuronFC(3, 1, "sigmoid");
	
	g->out = g->sequence[6];
	g->sequence[7] = new NeuronConst(1, 1);
	g->ans = g->sequence[7];
	//g->sequence[8] = new NeuronADELTA2();
	g->sequence[8] = new NeuronCrossEntropy();
	
	g->loss = g->sequence[8];
	//((NeuronADELTA2*)(g->loss))->x = 0.25;
	//SGD_Optimizer opt(g,0.3,0);
	//AdaGrad_Optimizer opt(g);
	//RMSProp_Optimizer opt(g);
	//Adam_Optimizer opt(g);
	ConjGradImproved_Optimizer opt(g, &d);

	Neuron::connect(*(g->sequence[0]), *(g->sequence[3]), FC_IN);
	Neuron::connect(*(g->sequence[1]), *(g->sequence[3]), FC_W);
	Neuron::connect(*(g->sequence[2]), *(g->sequence[3]), FC_B);
	Neuron::connect(*(g->sequence[3]), *(g->sequence[6]), FC_IN);
	Neuron::connect(*(g->sequence[4]), *(g->sequence[6]), FC_W);
	Neuron::connect(*(g->sequence[5]), *(g->sequence[6]), FC_B);
	Neuron::connect(*(g->sequence[6]), *(g->sequence[8]));
	Neuron::connect(*(g->sequence[7]), *(g->sequence[8]));
	g->GetSquence();
	d.FromFile();
	Normalized_Initializer init(g,3);
	init.run();
	//g->ReadArgsBin("args");
	//g->ReadArgsTxt("args.txt");
	train(&opt, &d, g,100000,0.001);
	//d.Init();
	//g->reset();
	//g->resetGrad();
	//d.putData();
	//d.putData();
	//g->run();
	//g->bp();
	//opt.run();
	//g->loss->out->Print();
	//g->out->out->Print();
	//d.disConnect();
	d.TestBatch();
	d.disConnect();
	//g->SaveArgsBin("args");
	g->SaveArgsTxt("args.txt");
	delete g;
	/*matmulTrans Test
	Matrix* a = new Matrix(1, 2);
	Matrix* b = new Matrix(2, 2, 3);
	Matrix* c = new Matrix(1, 3);
	Matrix* z = new Matrix(1, 3);
	a->alloc();
	b->alloc();
	c->alloc();
	z->alloc();
	z->Reset(3);
	a->Reset(3);
	a->data[1] = 2;
	b->Reset(4);
	b->MAT_AT2(0, 0) = 6;
	b->MAT_AT2(0, 1) = 5;
	b->MAT_AT2(0, 2) = 1;
	b->MAT_AT2(1, 0) = 7;
	b->MAT_AT2(1, 2) = 2;
	c->matmulTrans(*a, *b, *z, none);
	a->Print();
	b->Print();
	c->Print();
	delete a;
	delete b;
	delete c;
	delete z;*/
	PS;
}