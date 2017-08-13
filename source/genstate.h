#pragma once

namespace c2
{
	struct genstate
	{
		bool			code;
		bool			unique;
		genstate();
		~genstate();
	};
	extern genstate		gen;
}