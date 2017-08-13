#include "aref.h"

#pragma once

namespace c2
{
	struct segment : public aref<unsigned char>
	{
		unsigned		rvabase;
		int				index;
		segment();
		void			add(unsigned char a);
		unsigned char*	alloc(unsigned count);
		int				rel(const void* p) const { return (char*)p - (char*)data; }
	};
	extern unsigned		secbbs;
	extern segment		secdata;
	extern segment		seccode;
	extern segment		secstr;
}
