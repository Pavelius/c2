#include "crt.h"
#include "dasm.h"
#include "evalue.h"
#include "io.h"
#include "files.h"
#include "evalue.h"

static void error(c2::messages m, const c2::type* module, const c2::type* member, const char* parameters)
{
	char temp[4096];
	szprintv(temp, getstr(m), parameters);
	printcnf("Error: ");
	printcnf(temp);
	printcnf("\n");
}

static void status(c2::messages m, const c2::type* module, const c2::type* member, const char* parameters)
{
	switch(m)
	{
	case c2::StatusStartParse:
		printc("Module %1\n", module->id);
		break;
	case c2::StatusDeclare:
		//printc("Declare %1\n", member->id);
		break;
	case c2::StatusCompileMethod:
		printc("Compile %1.%2()\n", module->id, member->id);
		break;
	}
}

int main(int argc, char *argv[])
{
	if(argc<2)
	{
		printc("C2 compiler. Copyright (c) by Pavel Chistyakov, 2015-2017\n");
		printc("Options:\n");
		printc("-I	specified library path (like -Id:/libs)\n");
		printc("-C	specified compiled source path (like -Cd:/projects/test)\n");
		printc("-P	specified platform source path (like -Pc:/windows/system32)\n");
		printc("-O	specified output file name (like -Od:/projects/test/test.exe)\n");
	//	return 0;
	}
	c2::errorproc = error;
	c2::statusproc = status;
	c2::urls::project = "projects/anytest";
	c2::urls::output = "output";
	c2::urls::library = "library";
	c2::urls::platform = "C:/windows/system32";
	c2::type::cleanup();
	c2::backend = c2::evalue::plugin::find("asm");
	if(!c2::backend)
		return 0;
	c2::type::compile(szdup("main"), szdup("main"));
	c2::type::link(szdup("anytest"));
	return 0;
}