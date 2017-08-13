#include "evalue.h"

using namespace c2;

evalue::evalue() : result(type::i32), lvalue(0), offset(0), reg(Const), next(0)
{
}

evalue::evalue(evalue* e) : evalue()
{
	next = e;
}

void evalue::set(int value)
{
	this->result = type::i32;
	this->offset = value;
	this->lvalue = 0;
	this->reg = Const;
}

void evalue::set(type* value)
{
	if(!value)
		set(0);
	else if(value->istype())
	{
		this->result = value;
		this->offset = 0;
		this->lvalue = 0;
		this->reg = Const;
	}
	else if(value->isconstant())
	{
		set(value->value);
		this->result = value->result;
	}
	else
	{
		this->result = value->result;
		this->offset = 0;
		this->lvalue = value;
		this->reg = Const;
	}
}

void evalue::set(const evalue& e)
{
	result = e.result;
	lvalue = e.lvalue;
	offset = e.offset;
	reg = e.reg;
}

void evalue::clear()
{
	evalue();
}

void evalue::load(registers r)
{
}