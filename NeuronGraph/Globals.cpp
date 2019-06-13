#include"Globals.h"
double sigmoid(double x)
{
	return 1 / (1 + exp(-x));
}
double dsigmoid(double y)
{
	return y * (1 - y);
}
double relu(double x)
{
	return x > 0 ? x : 0;
}
double drelu(double y)
{
	return y > 0 ? 1 : 0;
}
double nntanh(double x)
{
	double tmp = exp(2 * x);
	return (tmp - 1) / (tmp + 1);
}
double dnntanh(double y)
{
	return 1 - y * y;
}
double none(double x)
{
	return x;
}