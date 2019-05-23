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
double none(double x)
{
	return x;
}