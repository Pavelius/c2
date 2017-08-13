#include "type.h"

#pragma once

namespace c2
{
	enum registers : char {
		Eax, Ebx, Ecx, Edx, Esi, Edi, Esp, Ebp,
		Const,
	};
	enum sectiontypes {
		Executable, Literal
	};
	struct evalue
	{
		type*			result;
		type*			lvalue;
		int				offset;
		registers		reg;
		evalue*			next;
		//
		evalue();
		evalue(evalue* e);
		//
		void			clear();
		bool			isconst() const { return reg==Const; }
		bool			islvalue() const { return lvalue != 0 || result->ispointer(); }
		void			load(registers r = Eax);
		void			set(int value);
		void			set(type* symbol);
		void			set(const evalue& e);
	};
}
