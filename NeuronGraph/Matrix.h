#pragma once
#include"Globals.h"
#define FOR_MAT for(int i=0;i<size;i++)
#define MAT_AT2(j,i) dp.m[j].d[i]//获取对应的值
#define MAT_AT3(k,j,i) dp.m[k].m[j].d[i]//获取对应的值
#define MAT_AT4(l,k,j,i) dp.m[l].m[k].m[j].d[i]//获取对应的值
class Matrix
{
private:
	bool needDestroy;	//是否需要销毁实际数据
public:
	double* data;	//实际数据
	int dim;	//维度
	int* dims;	//每一维长度
	int size;	//总空间
	bool haveData;	//是否已分配空间
	
	union matrix
	{
		matrix* m;	//矩阵数组
		double *d;
	}dp;	//实际仅有数据指针
	//matrix* At(int d, ...);
//public:
	Matrix();
	Matrix(const Matrix*);
	Matrix(int _dim,int* _dims);	//此时不分配空间
	void Set(int _dim, int* _dims);	//此时不分配空间
	Matrix(int _dim,...);		//此时不分配空间
	void SetDims(int _dim, ...);
	void FromFile(FILE* fp);
	~Matrix();
	void alloc();				//根据定义分配空间,注意所有空间分配为连续的；同时设置needDestroy
	//_mat* operator[](int indx);
	void Randomize(const double absRange = 1);
	void Reset(const double v=0);	//set everything to zero
	static void add(Matrix& a,const Matrix& b,const Matrix& c);	//a=b+c，反向由copy实现
	static void add(Matrix& a,const Matrix& b,const Matrix& c,const double x = 1,const double y=1);	//a=xb+yc，反向由xcopy实现
	void matmulTrans(const Matrix& x, const Matrix& w,const Matrix& b,double(*func)(double));	//this=func(xw+b)
	void DmatmulTrans(const Matrix& x, const Matrix& w, Matrix& dx, Matrix& dw, Matrix& db, const Matrix& out, double(*func)(double));	//this=func(xw+b)的反向(此时的func为func的导数)
	void addSquare(const Matrix& a, const double x = 1);	//this=x*a*a
	void DaddSquare(Matrix& da, const double x = 1)const;	//this=x*a*a的反向,da为结果的反向
	double L2()const;	//L2范数
	void DL2(const Matrix& a,const double dL2,const double x=1);	//this=a的L2范数*x的反向，dL2为范数的偏差
	double delta2(const Matrix& a,const double x);	//x||(this-a)||^2
	void Ddelta2(const Matrix& a, const Matrix& b, const double dout,const double x);	//x||(a-b)||^2的反向
	void square();	//this=this*this
	void inc(const Matrix& a,const double x=1);	//this+=xa，反向用xcopy实现
	void incSqr(const Matrix& a);	//this+=a*a
	void divideAndSqrt(const double epsilon, const double delta, const Matrix& r, const Matrix& g);	//this=epsilon/(delta+sqrt(r))*g
	void divideAndSqrt2(const double epsilon, const double delta, const Matrix& r, const Matrix& g);	//this=epsilon/sqrt(delta+r)*g
	void inc(const double a=0);	//this+=a
	void kinc2(const double k1, const double k2, const Matrix& b);	//this=k1*this+k2*b*b
	void mul(const double a = 1);	//this*=a
	void copy(const Matrix& a);	//this=a
	void xcopy(const Matrix& a,const double x=1);	//this=xa
	void getAdamDelta(Matrix& s,Matrix& r, const Matrix& g,const double _ro1, const double _ro2, const double ro1, const double ro2,const double eps,const double del );//直接计算adam optimizer结果
	void assignTo(const Matrix* a);	//使未进行空间分配的this的数据地址与已分配空间的a相同
	//static bool Connect(Matrix& a, Matrix& b);		//连接时分配空间，同时返回空间是否由a分配
	void Print();
private:
	//递归函数定义
	void _assignTo(matrix* m,int d,double*& offset);	//使未进行空间分配的this的数据地址与已分配空间的a相同
	void _destroy(matrix* m,int d);
	void _print(matrix* m, int d);
};

