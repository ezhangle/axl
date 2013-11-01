#pragma once

#include "axl_jncc_CmdLine.h"
#include "axl_jncc_OutStream.h"

//.............................................................................

enum
{
	EJnc_CompilerVersion = MAKELONG (0, MAKEWORD (0, 1))
};

//.............................................................................

enum EJncError
{
	EJncError_Success = 0,
	EJncError_InvalidCmdLine,
	EJncError_IoFailure,
	EJncError_CompileFailure,
	EJncError_RunFailure,
};

//.............................................................................

void
PrintVersion (COutStream* pOutStream);

void
PrintUsage (COutStream* pOutStream);

//.............................................................................

class CStdLib: public jnc::CStdLib
{
public:
	CStdLib ();

	void
	Export (
		jnc::CModule* pModule,
		jnc::CRuntime* pRuntime
		);

	static
	int
	Printf (
		const char* pFormat,
		...
		);
};

//.............................................................................

class CJnc
{
protected:
	static CJnc* m_pCurrentJnc;

	CCmdLine* m_pCmdLine;
	COutStream* m_pOutStream;

	jnc::CModule m_Module;
	jnc::CRuntime m_Runtime;
	CStdLib m_StdLib;

public:
	CJnc ()
	{
		m_pCurrentJnc = this;
		m_pCmdLine = NULL;
		m_pOutStream = NULL;
	}

	static
	CJnc*
	GetCurrentJnc ()
	{
		return m_pCurrentJnc;
	}

	COutStream*
	GetOutStream ()
	{
		return m_pOutStream;
	}

	int
	Run (
		CCmdLine* pCmdLine,
		COutStream* pOutStream
		);

protected:
	bool
	Compile (
		const char* pFileName,
		const char* pSource,
		size_t Length
		);

	bool
	Jit ();

	void
	PrintLlvmIr ();

	void
	PrintDisassembly ();

	bool
	RunFunction (int* pReturnValue = NULL);

	bool
	RunFunction (
		jnc::CFunction* pFunction,
		int* pReturnValue = NULL
		);

protected:
	int
	Server ();

	int
	Client (
		SOCKET Socket,
		sockaddr_in* pSockAddr
		);
};

//.............................................................................
