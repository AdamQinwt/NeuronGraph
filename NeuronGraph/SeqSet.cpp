#include "SeqSet.h"

SeqSet::SeqSet(int count,Neuron** seq,int& finished)
{
	v.clear();
	int i,j;
	bool flag;
	for (i = 0; i < count; i++)
	{
		if (seq[i]->ready>0) continue;
		if (seq[i]->ready < 0)
		{
			seq[i]->ready = 1; continue;
		}
		flag = 1;
		for (j = 0; j < seq[i]->prev.size(); j++)
		{
			if (seq[i]->prev[j]->ready!=1)
			{
				flag = 0;
				break;
			}
		}
		if (flag)
		{
			//put into this set and set ready = -1
			v.push_back(seq[i]);
			seq[i]->ready = -1;
			finished++;
		}
	}
}
SeqSet::SeqSet()
{
	v.clear();
}
SeqSet::~SeqSet()
{
}
