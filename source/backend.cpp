#include "backend.h"
#include "crt.h"

using namespace c2;

backend* backend::first;
backend* backend::current;

backend::backend(const char* progid) : progid(progid)
{
	seqlink(this);
}

backend* backend::find(const char* progid)
{
	for(auto p = first; p; p = p->next)
	{
		if(strcmp(p->progid, progid) == 0)
			return p;
	}
	return 0;
}