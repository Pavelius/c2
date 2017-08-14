#include "type.h"

#pragma once

namespace c2
{
	enum registers : char {
		Eax, Ebx, Ecx, Edx, Esi, Edi, Esp, Ebp,
		Const,
	};
	struct evalue
	{
		type*			result;
		registers		reg;
		int				offset;
		type*			sym;
		evalue*			next;
		//
		evalue();
		evalue(evalue* e);
		//
		void			clear();
		bool			isconst() const { return reg==Const; }
		bool			islvalue() const { return sym != 0 || result->ispointer(); }
		//void			load(registers r = Eax);
		void			set(int value);
		void			set(registers value);
		void			set(type* symbol);
		void			set(const evalue& e);
	};
}
