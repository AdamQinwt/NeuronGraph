#pragma once
#include"Globals.h"
#define FOR_MAT for(int i=0;i<size;i++)
class Matrix
{
private:
	bool needDestroy;	//�Ƿ���Ҫ����ʵ������
public:
	double* data;	//ʵ������
	int dim;	//ά��
	int* dims;	//ÿһά����
	int size;	//�ܿռ�
	bool haveData;	//�Ƿ��ѷ���ռ�
	
	union matrix
	{
		matrix* m;	//��������
		double *d;
	}dp;	//ʵ�ʽ�������ָ��
	//matrix* At(int d, ...);
//public:
	Matrix();
	Matrix(const Matrix*);
	Matrix(int _dim,int* _dims);	//��ʱ������ռ�
	void Set(int _dim, int* _dims);	//��ʱ������ռ�
	Matrix(int _dim,...);		//��ʱ������ռ�
	void SetDims(int _dim, ...);
	void FromFile(FILE* fp);
	~Matrix();
	void alloc();				//���ݶ������ռ�,ע�����пռ����Ϊ�����ģ�ͬʱ����needDestroy
	//_mat* operator[](int indx);
	void Randomize(const double absRange = 1);
	void Reset(const double v=0);	//set everything to zero
	static void add(Matrix& a,const Matrix& b,const Matrix& c);	//a=b+c��������copyʵ��
	static void add(Matrix& a,const Matrix& b,const Matrix& c,const double x = 1,const double y=1);	//a=xb+yc��������xcopyʵ��
	void matmulTrans(const Matrix& x, const Matrix& w,const Matrix& b,double(*func)(double));	//this=func(xw+b)
	void DmatmulTrans(const Matrix& x, const Matrix& w, Matrix& dx, Matrix& dw, Matrix& db, const Matrix& out, double(*func)(double));	//this=func(xw+b)�ķ���(��ʱ��funcΪfunc�ĵ���)
	void addSquare(const Matrix& a, const double x = 1);	//this=x*a*a
	void DaddSquare(Matrix& da, const double x = 1)const;	//this=x*a*a�ķ���,daΪ����ķ���
	double L2()const;	//L2����
	void DL2(const Matrix& a,const double dL2,const double x=1);	//this=a��L2����*x�ķ���dL2Ϊ������ƫ��
	double delta2(const Matrix& a,const double x);	//x||(this-a)||^2
	void Ddelta2(const Matrix& a, const Matrix& b, const double dout,const double x);	//x||(a-b)||^2�ķ���
	void square();	//this=this*this
	void inc(const Matrix& a,const double x=1);	//this+=xa��������xcopyʵ��
	void inc(const double a=0);	//this+=a
	void copy(const Matrix& a);	//this=a
	void xcopy(const Matrix& a,const double x=1);	//this=xa
	void assignTo(const Matrix* a);	//ʹδ���пռ�����this�����ݵ�ַ���ѷ���ռ��a��ͬ
	//static bool Connect(Matrix& a, Matrix& b);		//����ʱ����ռ䣬ͬʱ���ؿռ��Ƿ���a����
	void Print();
private:
	//�ݹ麯������
	void _assignTo(matrix* m,int d,double*& offset);	//ʹδ���пռ�����this�����ݵ�ַ���ѷ���ռ��a��ͬ
	void _destroy(matrix* m,int d);
	void _print(matrix* m, int d);
};

