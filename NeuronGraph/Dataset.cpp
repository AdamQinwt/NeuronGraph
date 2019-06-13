#include "Dataset.h"
void Dataset::fromFile()
{
	//不分配空间读入
	for (int i = 0; i < batchSize; i++)
	{
		x[i]->FromFile(fp);
		ans[i]->FromFile(fp);
		cout << "input=" << endl << "\t";
		x[i]->Print();
		cout << "answer=" << endl << "\t";
		ans[i]->Print();
	}
}
void Dataset::FromFile()
{
	fscanf(fp, "%d", &count);
	//分配空间
	calcInfo();
	x = new Matrix*[batchSize];
	ans = new Matrix*[batchSize];
	din = new Matrix(dimIn,dimsIn);
	din->alloc();
	loss = new Matrix(1,1);
	loss->alloc();
	for (int i = 0; i < batchSize; i++)
	{
		x[i] = new Matrix(dimIn, dimsIn);
		x[i]->alloc();
		ans[i] = new Matrix(dimOut, dimsOut);
		ans[i]->alloc();
	}
	//fromFile();
}
void Dataset::putData()
{
	g->in->out = x[indx];
	g->ans->out = ans[indx];
	indx++;
	if (indx == count) indx = 0;
}
void Dataset::Init()
{
	g->loss->out->assignTo(loss);
	g->loss->dout->assignTo(loss);
	loss->Reset(1);
	g->in->next[0]->din[g->in->indxAsOut]->assignTo(din);
}
void Dataset::calcInfo()
{
	if (!count) return;
	if (batchSize == 1)
	{
		batch = count;
		remainder = 0;
	}
	else if (batchSize)
	{
		//若batch大小确定
		batch = count / batchSize;
		remainder = count % batchSize;
		if (remainder) batch++;
	}
	else if (batch)
	{
		//若batch数量确定
		batchSize = count / batch;
		remainder = count % batch;
		if (remainder)
		{
			batchSize++;
			remainder = count % batchSize;
		}
	}
}
Dataset::Dataset(const char* fname, NeuronGraph* _g):count(0),batch(1),batchSize(0),remainder(0),g(_g)
{
	fp=fopen(fname,"r");
}
double Dataset::DoBatch()
{
	//fromFile();
	double loss = 0;
	for (int i = 0; i < count; i++)
	{
		g->resetGrad();
		g->reset();
		putData();
		g->run();
		g->bp();
		loss += g->loss->out->data[0];
	}
	return loss / count;
}
void Dataset::TestBatch()
{
	//fromFile();
	for (int i = 0; i < count; i++)
	{
		g->reset();
		putData();
		g->run();
		g->out->out->Print();
	}
}
void Dataset::SetIn(int _dim, ...)
{
	dimIn = _dim;
	dimsIn = new int[dimIn];
	va_list va;
	va_start(va, _dim);
	for (int i = 0; i < _dim; i++)
	{
		dimsIn[i] = va_arg(va, int);
	}
	va_end(va);
}
void Dataset::SetOut(int _dim, ...)
{
	dimOut = _dim;
	dimsOut = new int[dimOut];
	va_list va;
	va_start(va, _dim);
	for (int i = 0; i < _dim; i++)
	{
		dimsOut[i] = va_arg(va, int);
	}
	va_end(va);
}
void Dataset::disConnect()
{
	g->in->next[0]->in[g->in->indxAsOut] = nullptr;
	g->ans->next[0]->in[g->ans->indxAsOut] = nullptr;
	g->in->out = nullptr;
	g->ans->out = nullptr;
}
Dataset::~Dataset()
{
	if(fp) fclose(fp);
	for (int i = 0; i < batchSize; i++)
	{
		delete x[i];
		delete ans[i];
	}
	delete[] x;
	delete[] ans;
	delete[] dimsIn;
	delete[] dimsOut;
}
