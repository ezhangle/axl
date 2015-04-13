#include "pch.h"
#include "axl_fsm_RegExp.h"
#include "axl_rtl_AutoPtrArray.h"
#include "axl_mt_LongJmpTry.h"
#include "axl_mt_DynamicLibrary.h"

//.............................................................................

void bar ()
{
	printf ("bar -- throwing...\n");
	AXL_MT_LONG_JMP_THROW ();	
}

void foo ()
{
	AXL_MT_BEGIN_LONG_JMP_TRY ()
	{
		bar ();
	}
	AXL_MT_LONG_JMP_CATCH ()
	{
		printf ("exception caught\n");
	}
	AXL_MT_END_LONG_JMP_TRY ()

	AXL_MT_BEGIN_LONG_JMP_TRY ()
	{
		bar ();
	}
	AXL_MT_END_LONG_JMP_TRY ()

	printf ("done\n");
}

#if (_AXL_ENV == AXL_ENV_WIN)
int
wmain (
	int argc,
	wchar_t* argv []
	)
#else
int
main (
	int argc,
	char* argv []
	)
#endif
{
	bool result;

	printf ("main ()\n");

	mt::DynamicLibrary dl;
	
	result = dl.load ("libc.so.6");
	if (!result)
	{
		printf ("dl.load failed: %s\n", err::getLastError ().getDescription ().cc ());
		return -1;
	}

	typedef int Printf (const char*, ...);
	Printf* prn = (Printf*) dl.getFunction ("printf");
	if (!prn)
	{
		printf ("dl.load failed: %s\n", err::getLastError ().getDescription ().cc ());
		return -1;
	}

	prn ("hui govno i muravei %d\n", 123);

	foo ();

	char const* src [] = 
	{
		"'\\x02' V '\\r'",
	};

	fsm::RegExp regExp;	
	fsm::RegExpCompiler regExpCompiler (&regExp);

	for (size_t i = 0; i < countof (src); i++)
	{
		bool result = regExpCompiler.incrementalCompile (src [i]);
		if (!result)
		{
			printf ("error: %s\n", err::getLastError ().getDescription ().cc ());
			return -1;
		}
	}

	regExpCompiler.finalize ();

	regExp.print ();
	return 0;
}

//.............................................................................
