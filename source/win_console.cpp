#include "crt.h"
#include "win.h"

void printcnf(const char* text)
{
	unsigned result;
	WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), text, zlen(text), &result, 0);
}

void printc(const char* format, ...)
{
	char temp[4096 * 4];
	szprintv(temp, format, xva_start(format));
	printcnf(temp);
}