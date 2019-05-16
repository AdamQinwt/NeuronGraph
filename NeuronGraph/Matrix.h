#pragma once
#include<stdarg.h>
class Matrix
{
private:
	int dim;	//ά��
	int* dims;	//ÿһά����
	union _mat
	{
		_mat* m;
		double d;
	}data;
	double(*func)(double,double);	//�任����
public:
	Matrix(int dim,int* dims);	//��ʱ������ռ�
	Matrix(int dim,...);		//��ʱ������ռ�
	~Matrix();
	void alloc();				//ǿ�з���ռ䣨�����޷������ӱ���ʱ��
	void doFunc(double arg);
	void operator+=(const Matrix& m);
	void operator*=(const Matrix& m);
	void operator*=(const double x);
	void operator=(const Matrix& m);
	static void matmul(Matrix& m, const Matrix& a, const Matrix& b);
	static void Conv(Matrix& m, const Matrix& a, const Matrix& b,void* pairs);
	static void Connect(Matrix& a, Matrix& b);
};

