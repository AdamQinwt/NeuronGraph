#pragma once
#include"Globals.h"
#define FOR_MAT for(int i=0;i<size;i++)
#define MAT_AT2(j,i) dp.m[j].d[i]//��ȡ��Ӧ��ֵ
#define MAT_AT3(k,j,i) dp.m[k].m[j].d[i]//��ȡ��Ӧ��ֵ
#define MAT_AT4(l,k,j,i) dp.m[l].m[k].m[j].d[i]//��ȡ��Ӧ��ֵ
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
	//a=b+c��������copyʵ��
	static void add(Matrix& a,const Matrix& b,const Matrix& c);
	//a=xb+yc��������xcopyʵ��
	static void add(Matrix& a,const Matrix& b,const Matrix& c,const double x = 1,const double y=1);
	//this=func(xw+b)
	void matmulTrans(const Matrix& x, const Matrix& w,const Matrix& b,double(*func)(double));
	void DmatmulTrans(const Matrix& x, const Matrix& w, Matrix& dx, Matrix& dw, Matrix& db, const Matrix& out, double(*func)(double));	//this=func(xw+b)�ķ���(��ʱ��funcΪfunc�ĵ���)
	void addSquare(const Matrix& a, const double x = 1);	//this=x*a*a
	void DaddSquare(Matrix& da, const double x = 1)const;	//this=x*a*a�ķ���,daΪ����ķ���
	//L2����
	double L2()const;
	//this=a��L2����*x�ķ���dL2Ϊ������ƫ��
	void DL2(const Matrix& a,const double dL2,const double x=1);
	//x||(this-a)||^2
	double delta2(const Matrix& a,const double x);
	//x||(a-b)||^2�ķ���
	void Ddelta2(const Matrix& a, const Matrix& b, const double dout,const double x);
	//this=this*this
	void square();
	//this+=xa��������xcopyʵ��
	void inc(const Matrix& a,const double x=1);
	//this+=a*a
	void incSqr(const Matrix& a);
	//this=epsilon/(delta+sqrt(r))*g
	void divideAndSqrt(const double epsilon, const double delta, const Matrix& r, const Matrix& g);
	//this=epsilon/sqrt(delta+r)*g
	void divideAndSqrt2(const double epsilon, const double delta, const Matrix& r, const Matrix& g);
	//this+=a
	void inc(const double a = 0);
	//this=k1*this+k2*b*b
	void kinc2(const double k1, const double k2, const Matrix& b);
	//this=k1*this+k2*b
	void kinc(const double k1, const double k2, const Matrix& b);
	//this=k*(k1*this+k2*y)
	void kinck(const double k,const double k1, const double k2, const Matrix& a);
	//this+=k*a
	void inck(const double k,const Matrix& a);
	//this*=a
	void mul(const double a = 1);
	//this=a
	void copy(const Matrix& a);
	//this=xa
	void xcopy(const Matrix& a,const double x=1);
	//(a-b)^T a
	static double ConjGrad1(const Matrix& a,const Matrix& b);
	//ֱ�Ӽ���adam optimizer���
	void getAdamDelta(Matrix& s,Matrix& r, const Matrix& g,const double _ro1, const double _ro2, const double ro1, const double ro2,const double eps,const double del );
	//this=convolution(in)
	void conv(const Matrix& in, const Matrix& kernel, const Matrix& b, pointPair*** p,int ksize, double(*func)(double));
	//this=dout, calculate db,dkernel,din
	void dconv(const Matrix& in, const Matrix& kernel, const Matrix& b,Matrix& din,Matrix& dkernel,Matrix& db, pointPair*** p, int ksize, double(*func)(double));
	//this=max_pool(in)
	void maxPool(const Matrix& in, pointPair*** p,int*** maxIndx, int ksize);
	//this=dout, calculate din
	void dmaxPool(const Matrix& din, pointPair*** p,int*** maxIndx);
	//returns cross_entropy(this,q),this=out
	double crossEntropy(const Matrix& ans);
	//this=dcross_entropy
	void dcrossEntropy(const Matrix& out,const Matrix& ans,double dout);
	//change the value of this to between a and b
	void clip(const double a=1e-10,const double b=1-(1e-10));
	void assignTo(const Matrix* a);	//ʹδ���пռ�����this�����ݵ�ַ���ѷ���ռ��a��ͬ
	void Print();
	void WriteBin(FILE* fp);
	void ReadBin(FILE* fp);
	void WriteTxt(FILE* fp);
	void ReadTxt(FILE* fp);
private:
	//�ݹ麯������
	void _assignTo(matrix* m,int d,double*& offset);	//ʹδ���пռ�����this�����ݵ�ַ���ѷ���ռ��a��ͬ
	void _destroy(matrix* m,int d);
	void _print(matrix* m, int d);
};

