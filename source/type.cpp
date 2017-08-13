#include "autogrow.h"
#include "command.h"
#include "type.h"
#include "typeref.h"

using namespace c2;

// Standart types
type					type::i8[1];
type					type::i16[1];
type					type::i32[1];
type					type::u8[1];
type					type::u16[1];
type					type::u32[1];
type					type::v0[1];
type*					standart_types[] = {
	type::i8, type::i16, type::i32,
	type::u8, type::u16, type::u32,
	type::v0
};
// Some keywords
const char*				type::id_this;
const unsigned			pointer_size = 4;
//
static autogrow<type>	globals;
static type*			types; // main project types
static type*			types_ref; // pointers to main types
static type*			types_platform; // platform types

static type* new_type()
{
	return globals.add();
}

void type::clear()
{
	memset(this, 0, sizeof(type));
}

type* type::findtype(const char* id)
{
	// Стандартные типы
	for(auto p = types; p; p = p->next)
	{
		if(p->id == id)
			return p;
	}
	// Типы платформы
	for(auto p = types_platform; p; p = p->next)
	{
		if(p->id == id)
			return p;
	}
	return 0;
}

type* type::findmembertype(const char* id, int modifier_unsigned)
{
	// Найдем стандартный тип
	for(auto e : standart_types)
	{
		if(e->id == id)
			return e;
	}
	// Маленькие типы
	if(strcmp(id, "bool") == 0 || strcmp(id, "char") == 0)
	{
		if(modifier_unsigned)
			return type::u8;
		return type::i8;
	}
	// Короткое число
	if(strcmp(id, "short") == 0)
	{
		if(modifier_unsigned)
			return type::u16;
		return type::i16;
	}
	// Целое число
	if(strcmp(id, "int") == 0)
	{
		if(modifier_unsigned)
			return type::u32;
		return type::i32;
	}
	// Другие импортируемые типы
	for(auto p = refs; p; p = p->next)
	{
		if(p->id == id_this)
			continue;
		if(p->id == id)
			return p->type;
	}
	return 0;
}

type* type::findmembers(const char* id)
{
	// Найдем члены объявленные в теле
	auto m = find(id);
	if(m)
		return m;
	if(istype())
	{
		// Тип может быть основан на базовом, найдем его элементы
		for(auto p = child; p; p = p->next)
		{
			if(p->id != id_this)
				break;
			auto m = p->findmembers(id);
			if(m)
				return m;
		}
		// Найдем члены элементов, импортированных как this
		for(auto p = refs; p; p = p->next)
		{
			if(p->id == id_this)
			{
				for(auto m = p->type->child; m; m = m->next)
				{
					if(m->is(Private))
						continue;
					if(m->id == id)
						return m;
				}
			}
			else if(p->id == id)
				return p->type;
		}
	}
	return 0;
}

type* type::find(const char* id)
{
	// Найдем подчиненные элементы
	for(auto p = child; p; p = p->next)
	{
		if(p->id == id)
			return p;
	}
	return 0;
}

static bool szmatch(const char* text, const char* name)
{
	while(*name)
	{
		if(*name++ != *text++)
			return false;
	}
	return true;
}

static bool isplatformid(const char* id)
{
	return szmatch(id, "platform.");
}

type* type::create(const char* id)
{
	auto p = new_type();
	p->clear();
	p->id = id;
	if(isplatformid(id))
	{
		if(!types_platform)
			types_platform = p;
		else
			seqlast(types_platform)->next = p;
	}
	else
	{
		if(!types)
			types = p;
		else
			seqlast(types)->next = p;
	}
	return p;
}

type* type::create(const char* id, type* result, unsigned flags)
{
	if(!result)
		return 0;
	id = szdup(id);
	auto p = find(id);
	if(p)
		return p;
	p = new_type();
	p->clear();
	p->id = id;
	p->result = result;
	p->count = 1;
	p->size = result->size;
	if(result->ispointer())
		p->size = pointer_size;
	p->flags = flags;
	if(!child)
		child = p;
	else
		seqlast(child)->next = p;
	return p;
}

type* type::reference()
{
	if(!this)
		return 0;
	for(auto p = types_ref; p; p = p->next)
	{
		if(p->result == this)
			return p;
	}
	auto p = create(id);
	p->result = this;
	if(!types_ref)
		types_ref = p;
	else
		seqlast(types_ref)->next = p;
	return p;
}

bool type::isplatform() const
{
	if(istype())
		return isplatformid(id);
	else if(ismethod())
	{
		for(auto p = types_platform; p; p = p->next)
		{
			for(auto m = p; m; m = m->child)
			{
				if(m == this)
					return true;
			}
		}
	}
	return false;
}

type* type::dereference()
{
	if(!this)
		return 0;
	return result;
}

void type::setconstant(int value)
{
	this->value = value;
	this->count = -1;
	this->size = 0;
}

static void basetype(type* p, const char* name, unsigned size)
{
	p->id = szdup(name);
	p->size = size;
}

static void initialize_types()
{
	basetype(type::i8, "int8", 1);
	basetype(type::i16, "int16", 2);
	basetype(type::i32, "int32", 4);
	basetype(type::u8, "uint8", 1);
	basetype(type::u16, "uint16", 2);
	basetype(type::u32, "uint32", 4);
	basetype(type::v0, "void", 0);
}

extern void files_cleanup();
void type::cleanup()
{
	files_cleanup();
	globals.clear(); memset(globals.data, 0, sizeof(globals.data));
	typeref::cleanup();
	initialize_types();
}