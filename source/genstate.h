#pragma once

namespace c2
{
	struct genstate
	{
		bool			code;
		genstate();
		~genstate();
	};
	extern genstate		gen;
}