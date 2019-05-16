#pragma once
#include<stdarg.h>
class Matrix
{
private:
	int dim;	//维度
	int* dims;	//每一维长度
	union _mat
	{
		_mat* m;
		double d;
	}data;
	double(*func)(double,double);	//变换函数
public:
	Matrix(int dim,int* dims);	//此时不分配空间
	Matrix(int dim,...);		//此时不分配空间
	~Matrix();
	void alloc();				//强行分配空间（用于无法用连接表述时）
	void doFunc(double arg);
	void operator+=(const Matrix& m);
	void operator*=(const Matrix& m);
	void operator*=(const double x);
	void operator=(const Matrix& m);
	static void matmul(Matrix& m, const Matrix& a, const Matrix& b);
	static void Conv(Matrix& m, const Matrix& a, const Matrix& b,void* pairs);
	static void Connect(Matrix& a, Matrix& b);
};

