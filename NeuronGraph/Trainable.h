#pragma once
#include"Matrix.h"
#define ORIG 0
#define GRAD 1		//梯度
#define DELTA 2	//变化量
#define GRAD2 3	//二阶矩
class Trainable
{
	int* dims;
	int dim;
public:
	int cnt;
	Matrix* m;	//一系列同大小的matrix，用于存储不同数据
	void Alloc();	//分配空间
	Trainable();
	void Set(const int _dim,const int* _dims);	//需要复制
	~Trainable();
	//加入封装一些针对特定优化器的函数
};

