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
	AXL_JNC_API_BEGIN_LIB ()
		AXL_JNC_API_FUNCTION ("printf",  &Printf)
		AXL_JNC_API_LIB (jnc::CStdLib)
	AXL_JNC_API_END_LIB ()

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

	TCmdLine* m_pCmdLine;
	COutStream* m_pOutStream;

	jnc::CModule m_Module;
	jnc::CRuntime m_Runtime;

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
		TCmdLine* pCmdLine,
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
