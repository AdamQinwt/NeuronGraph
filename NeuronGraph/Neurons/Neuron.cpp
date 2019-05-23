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
//����������Ԫ������ռ䣩�������Ƿ���from����ռ䣬indxָʾ���ӵ�n2�ĵڼ�������λ�ã���n1��n2�еľ��������йض�ʵ�ʾ�����
//��Ҫ�Ƚ϶���ά�ȶ��٣���һ��ά�Ƚ��٣������ٵ�һ�����ռ䣬��һ��ָ��
//���ж�����Ϣ����ָ��
int Neuron::connect(Neuron& n1, Neuron& n2, int indx)
{
	//�ж��Ƿ��������
	if (n2.cnt == n2.capacity)
	{
		//���ɱ䣬����
		if (n2.isVarInput)
		{
			n2.expand();
		}
		//�����ɱ䣬����
		else return -1;
	}
	n1.next.push_back(&n2);
	n2.prev.push_back(&n1);
	n1.indxAsOut = indx > 0 ? indx : n2.cnt;
	if (n1.isTrain)
	{
		//ѵ�����������ڲ���������ࣩ����ռ�
		if (n1.out)
		{ 
			n2.in[n1.indxAsOut] = new Matrix(n1.out);
			n2.din[n1.indxAsOut] = new Matrix(n1.dout);
		}
		else
		{
			//���ȷ������
			n1.arg.Alloc();
			n1.out=new Matrix(n1.arg.m+ORIG);
			n1.dout = new Matrix(n1.arg.m+GRAD);
			n2.in[n1.indxAsOut] = new Matrix(n1.out);
			n2.din[n1.indxAsOut] = new Matrix(n1.dout);
		}
	}
	else if (n1.ty == CONSTANT)
	{
		//����������ռ䣬�������Ҳ�����գ�ÿ��ʹ��ʱ����
		n1.out = nullptr;
		n1.dout->alloc();
		n2.in[n1.indxAsOut] = nullptr;
		n2.din[n1.indxAsOut] = new Matrix(n1.dout);
	}
	else
	{
		//���Ӳ�������Ϣ
		//��n1�ѷ���ռ䣬��ֱ�ӽ�n2���������ӵ�n1.out
		if (n1.out->haveData)
		{
			n2.in[n1.indxAsOut] = new Matrix(n1.out);
			n2.din[n1.indxAsOut] = new Matrix(n1.dout);
		}
		else
		{
			//���ȷ������
			n1.out->alloc();
			n1.dout->alloc();
			n2.in[n1.indxAsOut] = new Matrix(n1.out);
			n2.din[n1.indxAsOut] = new Matrix(n1.dout);
		}
	}
	n2.cnt++;
	return 0;
}