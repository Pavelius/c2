#include "evalue.h"

#pragma once

namespace c2
{
	struct backend
	{
		virtual void	operation(evalue& e1, evalue& e2, char* t1, char* t2) = 0;
		virtual void	operation(evalue& e1, char* t1, char* t2) = 0;
		virtual	int		label(int a) = 0;
	};
}
