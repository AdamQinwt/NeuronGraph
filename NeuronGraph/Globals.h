#ifndef GLOBALS_H
#define GLOBALS_H
#include<stdarg.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include<iostream>
using namespace std;
//��ʱʡ�����о��������ά���ж�
#define PS system("pause")
struct pointPair
{
	int ax, ay;
	int bx, by;
};
double sigmoid(double);
double dsigmoid(double);
double relu(double);
double drelu(double);
double nntanh(double);
double dnntanh(double);
double none(double);
#endif // !GLOBALS_H
