#include "backend.h"

using namespace c2;

struct backend_asm : public backend
{

	void operation(evalue& e1, evalue& e2, char* t1, char* t2) override
	{
	}

	void operation(evalue& e1, char* t1, char* t2)
	{
	}

	int label(int a)
	{
		return a;
	}

};