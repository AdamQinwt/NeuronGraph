#pragma once
#include"Matrix.h"
#define ORIG 0
#define GRAD 1		//�ݶ�
#define DELTA 2	//�仯��
#define GRAD2 3	//���׾�
class Trainable
{
	int* dims;
	int dim;
public:
	int cnt;
	Matrix* m;	//һϵ��ͬ��С��matrix�����ڴ洢��ͬ����
	void Alloc();	//����ռ�
	Trainable();
	void Set(const int _dim,const int* _dims);	//��Ҫ����
	~Trainable();
	//�����װһЩ����ض��Ż����ĺ���
};

