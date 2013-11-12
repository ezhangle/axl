#pragma once

#include "resource.h"       // main symbols

// CAstApp:
// See test_ast.cpp for the implementation of this class
//

class CAstApp : public CWinAppEx
{
public:
	CFont m_Font;

public:
	CAstApp();

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CAstApp theApp;

