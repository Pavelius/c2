#include "evalue.h"

using namespace c2;

// Различные способы адресации
// Число 12 - reg(Const), offset(12)
// Переменная А - reg(Const), offset(0), sym(A)
// Переменная А[5] - reg(Const), offset(5*sizeof(A)), sym(A)

evalue::evalue() : result(type::i32), sym(0), offset(0), reg(Const), next(0)
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
	this->sym = 0;
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
		this->sym = 0;
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
		this->sym = value;
		this->reg = Const;
	}
}

void evalue::set(const evalue& e)
{
	sym = e.sym;
	result = e.result;
	offset = e.offset;
	reg = e.reg;
}

void evalue::clear()
{
	evalue();
}

//void evalue::load(registers r)
//{
//}