// This file is part of AXL (R) Library
// Tibbo Technology Inc (C) 2004-2012. All rights reserved
// Author: Vladimir Gladkov

#pragma once

namespace axl {
namespace jnc {

//.............................................................................

enum EToken
{
	EToken_Eof = 0,
	EToken_Error = -1,
	EToken_Identifier = 256,
	EToken_Integer,
	EToken_Fp,
	EToken_Literal,
	EToken_Import,
	EToken_Namespace,
	EToken_Using,
	EToken_Pack,
	EToken_Typedef,
	EToken_Static,
	EToken_Const,
	EToken_Public,
	EToken_Private,
	EToken_Void,
	EToken_Bool,
	EToken_Int,
	EToken_Char,
	EToken_Short,
	EToken_Long,
	EToken_Signed,
	EToken_Unsigned,
	EToken_BigEndian,
	EToken_LittleEndian,
	EToken_Float,
	EToken_Double,
	EToken_WChar,
	EToken_Int8,
	EToken_Int16,
	EToken_Int32,
	EToken_Int64,
	EToken_Variant,
	EToken_Auto,
	EToken_Enum,
	EToken_EnumC,
	EToken_Struct,
	EToken_Union,
	EToken_Class,
	EToken_Interface,
	EToken_Property,
	EToken_Get,
	EToken_Set,
	EToken_SizeOf,
	EToken_TypeOf,
	EToken_If,
	EToken_Else,
	EToken_For,
	EToken_While,
	EToken_Do,
	EToken_Break,
	EToken_Continue,
	EToken_Return,
	EToken_Switch,
	EToken_Case,
	EToken_Default,
	EToken_True,
	EToken_False,
	EToken_Eq,
	EToken_Ne,
	EToken_Le,
	EToken_Ge,
	EToken_LogicalOr,
	EToken_LogicalAnd,
	EToken_Inc,
	EToken_Dec,
	EToken_Shl,
	EToken_Shr,
	EToken_MulAssign,
	EToken_DivAssign,
	EToken_ModAssign,
	EToken_AddAssign,
	EToken_SubAssign,
	EToken_ShlAssign,
	EToken_ShrAssign,
	EToken_AndAssign,
	EToken_XorAssign,
	EToken_OrAssign,
	EToken_Ellipsis,
};

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

AXL_PRS_BEGIN_TOKEN_NAME_MAP (CTokenName)
	AXL_PRS_TOKEN_NAME (EToken_Eof,          "eof")
	AXL_PRS_TOKEN_NAME (EToken_Error,        "error")
	AXL_PRS_TOKEN_NAME (EToken_Identifier,   "identifier")
	AXL_PRS_TOKEN_NAME (EToken_Integer,      "integer-constant")
	AXL_PRS_TOKEN_NAME (EToken_Fp,           "floating-point-constant")
	AXL_PRS_TOKEN_NAME (EToken_Literal,      "string-literal")
	AXL_PRS_TOKEN_NAME (EToken_Import,       "import")
	AXL_PRS_TOKEN_NAME (EToken_Namespace,    "namespace")
	AXL_PRS_TOKEN_NAME (EToken_Using,        "using")
	AXL_PRS_TOKEN_NAME (EToken_Typedef,      "typedef")
	AXL_PRS_TOKEN_NAME (EToken_Static,       "static")
	AXL_PRS_TOKEN_NAME (EToken_Const,        "const")
	AXL_PRS_TOKEN_NAME (EToken_Public,       "public")
	AXL_PRS_TOKEN_NAME (EToken_Private,      "private")
	AXL_PRS_TOKEN_NAME (EToken_Void,         "void")
	AXL_PRS_TOKEN_NAME (EToken_Bool,         "bool")
	AXL_PRS_TOKEN_NAME (EToken_Int,          "int")
	AXL_PRS_TOKEN_NAME (EToken_Char,         "char")
	AXL_PRS_TOKEN_NAME (EToken_Short,        "short")
	AXL_PRS_TOKEN_NAME (EToken_Long,         "long")
	AXL_PRS_TOKEN_NAME (EToken_Signed,       "signed")
	AXL_PRS_TOKEN_NAME (EToken_Unsigned,     "unsigned")
	AXL_PRS_TOKEN_NAME (EToken_BigEndian,    "bigendian")
	AXL_PRS_TOKEN_NAME (EToken_LittleEndian, "littleendian")
	AXL_PRS_TOKEN_NAME (EToken_Float,        "float")
	AXL_PRS_TOKEN_NAME (EToken_Double,       "double")
	AXL_PRS_TOKEN_NAME (EToken_WChar,        "wchar_t")
	AXL_PRS_TOKEN_NAME (EToken_Int8,         "__int8")
	AXL_PRS_TOKEN_NAME (EToken_Int16,        "__int16")
	AXL_PRS_TOKEN_NAME (EToken_Int32,        "__int32")
	AXL_PRS_TOKEN_NAME (EToken_Int64,        "__int64")
	AXL_PRS_TOKEN_NAME (EToken_Variant,      "variant")
	AXL_PRS_TOKEN_NAME (EToken_Auto,         "auto")
	AXL_PRS_TOKEN_NAME (EToken_Enum,         "enum")
	AXL_PRS_TOKEN_NAME (EToken_EnumC,        "enumc")
	AXL_PRS_TOKEN_NAME (EToken_Struct,       "struct")
	AXL_PRS_TOKEN_NAME (EToken_Union,        "union")
	AXL_PRS_TOKEN_NAME (EToken_Pack,         "pack")
	AXL_PRS_TOKEN_NAME (EToken_Class,        "class")
	AXL_PRS_TOKEN_NAME (EToken_Interface,    "interface")
	AXL_PRS_TOKEN_NAME (EToken_Property,     "property")
	AXL_PRS_TOKEN_NAME (EToken_SizeOf,       "sizeof")
	AXL_PRS_TOKEN_NAME (EToken_TypeOf,       "typeof")
	AXL_PRS_TOKEN_NAME (EToken_If,           "if")
	AXL_PRS_TOKEN_NAME (EToken_Else,         "else")
	AXL_PRS_TOKEN_NAME (EToken_For,          "for")
	AXL_PRS_TOKEN_NAME (EToken_While,        "while")
	AXL_PRS_TOKEN_NAME (EToken_Do,           "do")
	AXL_PRS_TOKEN_NAME (EToken_Break,        "break")
	AXL_PRS_TOKEN_NAME (EToken_Continue,     "continue")
	AXL_PRS_TOKEN_NAME (EToken_Return,       "return")
	AXL_PRS_TOKEN_NAME (EToken_Switch,       "switch")
	AXL_PRS_TOKEN_NAME (EToken_Case,         "case")
	AXL_PRS_TOKEN_NAME (EToken_Default,      "default")
	AXL_PRS_TOKEN_NAME (EToken_True,         "true")
	AXL_PRS_TOKEN_NAME (EToken_False,        "false")
	AXL_PRS_TOKEN_NAME (EToken_Eq,           "==")
	AXL_PRS_TOKEN_NAME (EToken_Ne,           "!=")
	AXL_PRS_TOKEN_NAME (EToken_Le,           "<=")
	AXL_PRS_TOKEN_NAME (EToken_Ge,           ">=")
	AXL_PRS_TOKEN_NAME (EToken_LogicalOr,    "||")
	AXL_PRS_TOKEN_NAME (EToken_LogicalAnd,   "&&")	
	AXL_PRS_TOKEN_NAME (EToken_Inc,          "++")
	AXL_PRS_TOKEN_NAME (EToken_Dec,          "--")
	AXL_PRS_TOKEN_NAME (EToken_Shl,          "<<")
	AXL_PRS_TOKEN_NAME (EToken_Shr,          ">>")
	AXL_PRS_TOKEN_NAME (EToken_MulAssign,    "*=")
	AXL_PRS_TOKEN_NAME (EToken_DivAssign,    "/=")
	AXL_PRS_TOKEN_NAME (EToken_ModAssign,    "%=")
	AXL_PRS_TOKEN_NAME (EToken_AddAssign,    "+=")
	AXL_PRS_TOKEN_NAME (EToken_SubAssign,    "-=")
	AXL_PRS_TOKEN_NAME (EToken_ShlAssign,    "<<=")
	AXL_PRS_TOKEN_NAME (EToken_ShrAssign,    ">>=")
	AXL_PRS_TOKEN_NAME (EToken_AndAssign,    "&=")
	AXL_PRS_TOKEN_NAME (EToken_XorAssign,    "^=")
	AXL_PRS_TOKEN_NAME (EToken_OrAssign,     "|=")	
	AXL_PRS_TOKEN_NAME (EToken_Ellipsis,     "...")
		
AXL_PRS_END_TOKEN_NAME_MAP ();

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

typedef lex::CRagelTokenT <EToken, CTokenName> CToken;

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

class CLexer: public lex::CRagelLexerT <CLexer, CToken>
{
	friend class lex::CRagelLexerT <CLexer, CToken>;

protected:
	CToken*
	CreateStringToken (
		int Token,
		int Left = 0,
		int Right = 0
		)
	{
		CToken* pToken = CreateToken (Token);
		pToken->m_Data.m_String.Copy (ts + Left, pToken->m_Pos.m_Length - (Left + Right));
		return pToken;
	}

	CToken*
	CreateCharToken (int Token)
	{
		CToken* pToken = CreateToken (Token);
		pToken->m_Data.m_Integer = ts [1];
		return pToken;
	}

	CToken*
	CreateIntegerToken (
		int Radix = 10,
		int Left = 0
		)
	{
		CToken* pToken = CreateToken (EToken_Integer);
		pToken->m_Data.m_Integer = strtol (ts + Left, NULL, Radix);
		return pToken;
	}

	CToken*
	CreateFpToken ()
	{
		CToken* pToken = CreateToken (EToken_Fp);
		pToken->m_Data.m_Double = strtod (ts, NULL);
		return pToken;
	}

	CToken*
	CreateConstIntegerToken (int Value)
	{
		CToken* pToken = CreateToken (EToken_Integer);
		pToken->m_Data.m_Integer = Value;
		return pToken;
	}

	// implemented in *.rl

	void 
	Init ();

	bool
	Exec ();
};

//.............................................................................

} // namespace axl {
} // namespace jnc {
