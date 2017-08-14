#include "evalue.h"

#pragma once

namespace c2
{
	struct backend
	{
		const char*		progid;
		backend*		next;
		static backend*	first;
		static backend*	current;
		//
		backend(const char* progid);
		//
		virtual void	epilogue(type* module, type* member) = 0;
		static backend*	find(const char* progid);
		virtual void	operation(evalue& e1, evalue& e2, char t1, char t2 = 0) = 0;
		virtual void	operation(evalue& e1, char t1) = 0;
		virtual void	prologue(type* module, type* member) = 0;
		virtual	int		label(int a) = 0;
	};
}
