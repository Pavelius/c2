#include "segment.h"
#include "genstate.h"

using namespace c2;

segment		c2::seccode;
segment		c2::secdata;
segment		c2::secstr;
unsigned	c2::secbbs;

segment::segment() : rvabase(0), index(0)
{
	data = 0;
	count = 0;
}

void segment::add(unsigned char a)
{
	if(!gen.code)
		return;
	reserve();
	data[count++] = a;
}

unsigned char* segment::alloc(unsigned count)
{
	auto m = this->count;
	reserve(m + count);
	return data + m;
}