#include "Normalized_Initializer.h"



Normalized_Initializer::Normalized_Initializer(NeuronGraph* _g,int total):g(_g)
{
	r = total;
	r = sqrt(6 / r);
}


Normalized_Initializer::~Normalized_Initializer()
{
}
void Normalized_Initializer::run()
{
	for (int i = 0; i < g->count; i++)
	{
		if (g->sequence[i]->ty == VARIABLE)
			g->sequence[i]->out->Randomize(r);
	}
}
