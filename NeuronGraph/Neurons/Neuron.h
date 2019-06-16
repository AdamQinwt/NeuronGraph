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
	//区分不同类型
	type ty;
	bool isTrain;	//是否可训练
	bool isVarInput;	//是否可变输入
	int cnt;	//输入个数
	int capacity  ;	//输入个数
	Matrix** in,**din;	//输入可能有多个，用指针表示
	Matrix* out,*dout;	//输出只能有一个，用直接变量表示
	int indxAsOut;	//当前输出对于下一个神经元的位置

	int nbp;	//对单个节点而言已进行反向计算的次数
	Trainable arg;	//用于variable的额外参数
	//pointers of previous and next neurons
	vector<Neuron*> prev, next;
	
	virtual void init()=0; //初始化，包含一般的置0操作
	virtual void run()=0; //前向运算
	virtual void bp()=0; //后向运算
	void reset();
	void resetGrad();
	void expand();	//扩展输入空间
	//连接两个神经元（分配空间），返回是否由from分配空间，indx指示连接到n2的第几个输入位置（与n1在n2中的具体作用有关而实际决定）
	//所有额外信息另外指定
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

