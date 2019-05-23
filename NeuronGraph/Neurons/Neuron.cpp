#include "Neuron.h"
void Neuron::expand()
{
	capacity <<= 1;
	in = (Matrix**)realloc(in, capacity * sizeof(Matrix*));
}
void Neuron::reset()
{
	if (ty == CONSTANT || ty == VARIABLE) return;
	out->Reset();
	//dout->Reset();
}
void Neuron::resetGrad()
{
	if (ty == CONSTANT || ty == VARIABLE) return;
	dout->Reset();
}
//连接两个神经元（分配空间），返回是否由from分配空间，indx指示连接到n2的第几个输入位置（与n1在n2中的具体作用有关而实际决定）
//需要比较二者维度多少，若一侧维度较少，则在少的一侧分配空间，另一侧指向
//所有额外信息另外指定
int Neuron::connect(Neuron& n1, Neuron& n2, int indx)
{
	//判断是否可以连接
	if (n2.cnt == n2.capacity)
	{
		//若可变，扩容
		if (n2.isVarInput)
		{
			n2.expand();
		}
		//若不可变，结束
		else return -1;
	}
	n1.next.push_back(&n2);
	n2.prev.push_back(&n1);
	n1.indxAsOut = indx > 0 ? indx : n2.cnt;
	if (n1.isTrain)
	{
		//训练参数优先在参数（输出侧）分配空间
		if (n1.out)
		{ 
			n2.in[n1.indxAsOut] = new Matrix(n1.out);
			n2.din[n1.indxAsOut] = new Matrix(n1.dout);
		}
		else
		{
			//优先分配输出
			n1.arg.Alloc();
			n1.out=new Matrix(n1.arg.m+ORIG);
			n1.dout = new Matrix(n1.arg.m+GRAD);
			n2.in[n1.indxAsOut] = new Matrix(n1.out);
			n2.din[n1.indxAsOut] = new Matrix(n1.dout);
		}
	}
	else if (n1.ty == CONSTANT)
	{
		//常数不分配空间，在输出处也仅留空，每次使用时填入
		n1.out = nullptr;
		n1.dout->alloc();
		n2.in[n1.indxAsOut] = nullptr;
		n2.din[n1.indxAsOut] = new Matrix(n1.dout);
	}
	else
	{
		//连接并更新信息
		//若n1已分配空间，则直接将n2的输入连接到n1.out
		if (n1.out->haveData)
		{
			n2.in[n1.indxAsOut] = new Matrix(n1.out);
			n2.din[n1.indxAsOut] = new Matrix(n1.dout);
		}
		else
		{
			//优先分配输出
			n1.out->alloc();
			n1.dout->alloc();
			n2.in[n1.indxAsOut] = new Matrix(n1.out);
			n2.din[n1.indxAsOut] = new Matrix(n1.dout);
		}
	}
	n2.cnt++;
	return 0;
}