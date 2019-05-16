#pragma once
class Optimizer
{
public:
	virtual void run() = 0;
	Optimizer();
	~Optimizer();
};

