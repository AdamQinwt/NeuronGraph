#pragma once
#include<vector>
#include"../Trainable.h"
#include"../Matrix.h"

using namespace std;
enum  type{ CONSTANT, VARIABLE,FC, ADD, AXPB, CONV, MAX_POOL, AX, AX2,AL,AL2,ADELTA2,CE };
class Neuron
{
public:
	int ready;
	//���ֲ�ͬ����
	type ty;
	bool isTrain;	//�Ƿ��ѵ��
	bool isVarInput;	//�Ƿ�ɱ�����
	int cnt;	//�������
	int capacity  ;	//�������
	Matrix** in,**din;	//��������ж������ָ���ʾ
	Matrix* out,*dout;	//���ֻ����һ������ֱ�ӱ�����ʾ
	int indxAsOut;	//��ǰ���������һ����Ԫ��λ��

	int nbp;	//�Ե����ڵ�����ѽ��з������Ĵ���
	Trainable arg;	//����variable�Ķ������
	//pointers of previous and next neurons
	vector<Neuron*> prev, next;
	
	virtual void init()=0; //��ʼ��������һ�����0����
	virtual void run()=0; //ǰ������
	virtual void bp()=0; //��������
	void reset();
	void resetGrad();
	void expand();	//��չ����ռ�
	//����������Ԫ������ռ䣩�������Ƿ���from����ռ䣬indxָʾ���ӵ�n2�ĵڼ�������λ�ã���n1��n2�еľ��������йض�ʵ�ʾ�����
	//���ж�����Ϣ����ָ��
	static int connect(Neuron& n1,Neuron& n2,int indx=-1);
	virtual ~Neuron() {
		for (int i = 0; i < cnt; i++)
		{
			delete in[i];
			delete din[i];
		}
		delete[] in;
		delete[] din;
	};
	Neuron() {};
};

