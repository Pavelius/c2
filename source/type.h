#include "typeref.h"

#pragma once

namespace c2
{
	enum messages
	{
		ErrorUnexpectedSymbols, ErrorExpected1p,
		ErrorInvalidEscapeSequence,
		ErrorInvalid1p2pIn3p,
		ErrorCantFind1pWithName2p,
		ErrorOperation1pNotUsedWithOperands2pAnd3p,
		ErrorNeedSymbol, ErrorNeedConstantExpression, ErrorNeedIndentifier, ErrorNeedFunctionMember, ErrorNeedPointerOrArray, ErrorNeedLValue,
		ErrorLongNotUseWithThisType, ErrorShortNotUseWithThisType, ErrorUnsignedNotUseWithThisType,
		Error1pDontUse2pTimes,
		ErrorArrayOverflow, ErrorImportAlreadyHavePseudonim, ErrorModuleAlreadyImported,
		ErrorUnknownInstance, ErrorVoidReturnValue,
		ErrorKeyword1pUsedWithout2p,
		ErrorAssigmentWithoutEnumeratorMember, ErrorExpectedEnumeratorMember,
		ErrorSectionNumber,
		ErrorWrongParamNumber,
		ErrorNotImplement1p2p,
		ErrorCastType1pTo2p,
		ErrorOptions, ErrorCompilator, ErrorLinker,
		FirstError = ErrorUnexpectedSymbols, LastError = ErrorCastType1pTo2p,
		StatusStartParse, StatusEndParse, StatusLink1p, StatusKeyword,
		StatusDeclare,
		FirstStatus = StatusStartParse, LastStatus = StatusDeclare,
	};
	enum typeflags : char {
		Private, Static, Forward, Readed, Writed,
	};
	struct type
	{
		const char*		id; // name identifiers ('this' name for base type)
		unsigned		size; // size of type/requisit (total lenght is multiplied by count), 0 for method
		int				count; // 0 for type, 1+ for requisit, parameters count for method
		int				value;
		type*			result; // result of requisit or type pointer
		type*			child; // child requisits, list of params
		type*			next; // next element in chain
		typeref*		refs; // pseudonime and types
		unsigned		flags;
		operator bool() const { return id != 0; }
		//
		static type		i8[1];
		static type		i16[1];
		static type		i32[1];
		static type		u8[1];
		static type		u16[1];
		static type		u32[1];
		static type		v0[1];
		//
		static const char* id_this;
		//
		static type*	compile(const char* module_id);
		static type*	create(const char*  id);
		type*			create(const char*  id, type* result, unsigned flags);
		static void		cleanup();
		void			clear();
		type*			dereference();
		type*			find(const char* id);
		type*			findmembers(const char* id);
		type*			findmembertype(const char* id, int modifier_unsigned = 0);
		static type*	findtype(const char* id);
		unsigned		getlenght() const { return size*count; }
		unsigned		getparametercount() const { return ismethod() ? count : 0; }
		bool			is(typeflags value) const { return (flags&(1 << value)) != 0; }
		bool			isconstant() const { return count == -1 && size == 0; }
		bool			ispointer() const { return istype() && result; }
		bool			istype() const { return count == 0; }
		bool			ismember() const { return this && count > 0; }
		bool			ismethod() const { return this && ismember() && size == 0; }
		bool			isplatform() const;
		void			parse(bool quick_header = false);
		type*			reference();
		void			set(typeflags value) { flags |= 1 << value; }
		void			setconstant(int value);
		void			setmethod() { size = 0; }
	};
	void				status(messages m, ...);
	extern void(*errorproc)(messages m, const type* module, const type* member, const char* parameters);
	extern void(*statusproc)(messages m, const type* module, const type* member, const char* parameters);
}