// This file is part of AXL (R) Library
// Tibbo Technology Inc (C) 2004-2013. All rights reserved
// Author: Vladimir Gladkov

#pragma once

#define _AXL_GUI_QTFONT_H

#include "axl_gui_Font.h"

namespace axl {
namespace gui {

//.............................................................................

bool
GetFontDescFromFontInfo (
	const QFontInfo& FontInfo,
	TFontDesc* pFontDesc
	);

//.............................................................................

class CQtFont: public CFont
{
	friend class CQtEngine;

public:
	QFont m_QtFont;
	
public:
	CQtFont ();

	virtual
	bool
	IsMonospace ()
	{
		return QFontInfo (m_QtFont).fixedPitch ();
	}

	virtual
	TSize
	CalcTextSize (
		const char* pText,
		size_t Length = -1
		);
};

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

typedef CFontTupleT <CQtFont> CQtFontTuple;

//.............................................................................

} // namespace gui
} // namespace axl
