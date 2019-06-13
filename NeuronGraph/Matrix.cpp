#include "Matrix.h"

Matrix::Matrix():dim(0),haveData(0)
{
	//
}
Matrix::Matrix(int _dim,int* _dims) : dim(_dim),haveData(0)
{
	haveData = 0;
	dims = new int[dim];
	size = 1;
	for (int i = 0; i < dim; i++)
	{
		dims[i] = _dims[i];
		size *= dims[i];
	}
}
void Matrix::Set(int _dim, int* _dims)//此时不分配空间
{
	dim = _dim;
	haveData = 0;
	dims = new int[dim];
	size = 1;
	for (int i = 0; i < dim; i++)
	{
		dims[i] = _dims[i];
		size *= dims[i];
	}
}
Matrix::Matrix(int _dim,...) : dim(_dim), haveData(0)
{
	size = 1;
	va_list va;
	va_start(va, _dim);
	dims = new int[_dim];
	for (int i = 0; i < _dim; i++)
	{
		dims[i] = va_arg(va, int);
		size *= dims[i];
	}
	va_end(va);
	dp.m = NULL;
}
Matrix::Matrix(const Matrix* a)
{
	Set(a->dim, a->dims);
	assignTo(a);
}
void Matrix::SetDims(int _dim, ...)
{
	va_list va;
	va_start(va, _dim);
	dim = _dim;
	dims = new int[_dim];
	for (int i = 0; i < _dim; i++)
		dims[i] = va_arg(va, int);
	va_end(va);
	dp.m = NULL;
}
Matrix::~Matrix()
{
	if (haveData)
	{
		delete[] data;
		haveData = 0;
	}
	_destroy(&dp,0);
	delete[]dims;
}
void Matrix::Randomize(const double absRange)
{
	double x,d=absRange/0x800;
	FOR_MAT
	{
		x = rand() & 0xfff;
		x -= 0x800;
		data[i] = x*d;
	}
	Print();
}
void Matrix::Reset(const double v)	//set everything to zero, or something else
{
	if (!data) return;
	FOR_MAT
	{
		data[i] = v;
	}
}
void Matrix::add(Matrix& a, const Matrix& b, const Matrix& c)	//a=b+c
{
	int d,i;
	matrix* ma=&(a.dp);
	const matrix* mb=&(b.dp);
	const matrix* mc=&(c.dp);
	for (d = 0; d < a.dim; d++)
	{
		//
	}
}
void Matrix::add(Matrix& a, const Matrix& b, const Matrix& c, const double x, const double y)	//a=xb+yc
{
	for(int i=0;i<a.size;i++)
	{
		a.data[i] = x * b.data[i] + y * c.data[i];
	}
}
void Matrix::xcopy(const Matrix& a, const double x)	//this=xa
{
	if (x == 1)
	{
		FOR_MAT
		{
			data[i] = a.data[i];
		}
	}
	else
	{
		FOR_MAT
		{
			data[i] = x * a.data[i];
		}
	}
}
void Matrix::matmulTrans(const Matrix& x, const Matrix& w, const Matrix& b, double(*func)(double))	//this=func(xw+b)
{
	//此时已知this,x,b为1维，w为2维
	for (int i = 0; i < dims[0]; i++)
	{
		data[i] = b.data[i];
		//cout << "Initial data["<<i<<"]="<<data[i]<<endl;
		for (int j = 0; j < x.dims[0]; j++)
		{
			//cout<< "weight["<<j<<"]["<<i<<"]="<<w.dp.m[j].d[i]<<endl;
			data[i] += x.data[j] * w.dp.m[j].d[i];
		}
		data[i] = func(data[i]);
	}
}
void Matrix::DmatmulTrans(const Matrix& x, const Matrix& w,Matrix& dx,Matrix& dw, Matrix& db, const Matrix& out,double(*func)(double))
{
	//this=func(xw+b)的反向(此时的func为func的导数)
	double d;
	for (int i = 0; i < dims[0]; i++)
	{
		d = func(out.data[i])*data[i];
		db.data[i] += d;
		for (int j = 0; j < x.dims[0]; j++)
		{
			dx.data[j] += d * w.dp.m[j].d[i];
			dw.dp.m[j].d[i] += d * x.data[j];
		}
	}
}
void Matrix::addSquare(const Matrix& a, const double x)	//this+=x*a*a
{
	FOR_MAT
	{
		data[i] += x * a.data[i]*a.data[i];
	}
}
void Matrix::DaddSquare(Matrix& da, const double x)const	//this=x*a*a的反向,this为偏差
{
	double xx = x * 2;
	FOR_MAT
	{
		da.data[i] = data[i]*xx;
	}
}
double Matrix::L2()const	//L2范数
{
	double sum = 0;
	FOR_MAT
	{
		sum += data[i] * data[i];
	}
	return sum;
}
void Matrix::DL2(const Matrix& a, const double dL2, const double x)	//this=a的L2范数*x的反向
{
	double xx = dL2*x * 2;
	FOR_MAT
	{
		a.data[i] += xx * data[i];
	}
}
double Matrix::delta2(const Matrix& a, const double x)	//||(this-a)||
{
	double sum = 0, tmp;
	FOR_MAT
	{
		tmp = data[i] - a.data[i];
		sum += tmp * tmp;
	}
	return sum*x;
}
void Matrix::Ddelta2(const Matrix& a, const Matrix& b,const double dout, const double x)	//x||(a-b)||的反向
{
	double xx = 2 * dout*x;
	FOR_MAT
	{
		data[i] += xx * (a.data[i]-b.data[i]);
	}
}
void Matrix::square()	//this=this*this
{
	FOR_MAT
	{
		data[i] *= data[i];
	}
}
void Matrix::inc(const Matrix& a, const double x)	//this+=xa
{
	if (x == 1)
	{
		FOR_MAT
		{
			data[i] += a.data[i];
		}
	}
	else
	{
		FOR_MAT
		{
			data[i] += x * a.data[i];
		}
	}
}
void Matrix::inc(const double a)	//this+=a
{
	FOR_MAT
	{
		data[i] += a;
	}
}
void Matrix::kinc2(const double k1, const double k2, const Matrix& b)	//this=k1*this+k2*b
{
	FOR_MAT
	{
		data[i] = k1 * data[i] + k2 * b.data[i] * b.data[i];
	}
}
void Matrix::incSqr(const Matrix& a)
{
	FOR_MAT
	{
		data[i] += a.data[i] * a.data[i];
	}
}
void Matrix::divideAndSqrt(const double epsilon, const double delta, const Matrix& r, const Matrix& g)	//this=epsilon/(delta+sqrt(r))*g
{
	FOR_MAT
	{
		data[i] = epsilon / (delta + sqrt(r.data[i]))*g.data[i];
	}
}
void Matrix::divideAndSqrt2(const double epsilon, const double delta, const Matrix& r, const Matrix& g)	//this=epsilon/sqrt(delta+r)*g
{
	FOR_MAT
	{
		data[i] = epsilon / sqrt(delta + r.data[i])*g.data[i];
	}
}
void Matrix::mul(const double a)
{
	if (a == 1) return;
	if (!a) Reset();
	FOR_MAT
	{
		data[i] *= a;
	}
}
void Matrix::copy(const Matrix& a)	//this=a
{
	memcpy(data, a.data, size*sizeof(double));
}
void Matrix::getAdamDelta(Matrix& s, Matrix& r,const Matrix& g, const double _ro1, const double _ro2, const double ro1, const double ro2, const double eps, const double del)//直接计算adam optimizer结果
{
	FOR_MAT
	{
		s.data[i] = ro1 * s.data[i] + (1 - ro1)*g.data[i];
		r.data[i] = ro2 * r.data[i] + (1 - ro2)*g.data[i] * g.data[i];
		data[i] = -eps * s.data[i] / (1 - ro1) / (del + sqrt(r.data[i] / (1 - ro2)));
	}
}
void Matrix::assignTo(const Matrix* a)	//使未进行空间分配的this的数据地址与已分配空间的a相同
{
	data = a->data;
	double* tmp = a->data;
	_assignTo(&dp, 0, tmp);
}
void Matrix::alloc()
{
	data = new double[size];
	double* tmp = data;
	_assignTo(&dp, 0, tmp);
}
void Matrix::_assignTo(matrix* m, int d, double*& offset)	//使未进行空间分配的this的数据地址与offset
{
	if (d == dim - 1)
	{
		m->d = offset;
		offset += dims[d];
	}
	else
	{
		m->m = new matrix[dims[d]];
		for (int i = 0; i < dims[d]; i++)
		{
			_assignTo(m->m + i, d + 1, offset);
		}
	}
}
void Matrix::_destroy(matrix* m, int d)
{
	if (d >= dim - 2)
	{
		//m->d = offset;
	}
	else
	{
		for (int i = 0; i < dims[d]; i++)
		{
			_destroy(m->m + i, d + 1);
		}
		delete[] m->m;
	}
}
void Matrix::FromFile(FILE* fp)
{
	for (int i = 0; i < size; i++)
	{
		fscanf(fp, "%lf", data + i);
	}
}
void Matrix::_print(matrix* m, int d)
{
	if (d == dim - 1)
	{
		for (int i = 0; i < dims[d]; i++)
		{
			cout << m->d[i] << '\t';
		}
		cout << endl;
	}
	else
	{
		for (int i = 0; i < dims[d]; i++)
		{
			_print(m->m + i, d + 1);
		}
	}
}
void Matrix::Print()
{/*
	cout << "dims\t" << dim << endl;
	cout << "dims:\t";
	for (int i = 0; i < dim; i++)
	{
		cout << dims[i] << '\t';
	}
	cout << endl;*/
	_print(&dp, 0);
}