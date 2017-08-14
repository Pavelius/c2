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
		static type		lvalue_type[2];
		void			clear();
		void			dereference();
		bool			isconst() const { return reg==Const; }
		bool			islvalue() const { return sym != 0; }
		static int		localalloc(unsigned size);
		registers		getfree() const;
		void			getvalue();
		void			load(registers r);
		void			save(registers r);
		void			set(int value);
		void			set(type* symbol);
		void			set(const evalue& e);
		void			xchange(evalue& e);
	};
}
