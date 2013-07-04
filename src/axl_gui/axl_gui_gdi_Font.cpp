#include "pch.h"
#include "axl_gui_gdi_Font.h"
#include "axl_gui_gdi_Engine.h"
#include "axl_err_Error.h"

namespace axl {
namespace gui {
namespace gdi {

//.............................................................................

bool
BuildLogFont (
	LOGFONTW* pLogFont,
	const wchar_t* pFaceName,
	size_t PointSize,
	uint_t Flags
	)
{
	memset (pLogFont, 0, sizeof (LOGFONT));

	size_t Length = wcslen (pFaceName);

	memcpy (
		pLogFont->lfFaceName, 
		pFaceName, 
		AXL_MIN (countof (pLogFont->lfFaceName), Length) * sizeof (wchar_t)
		);

	pLogFont->lfCharSet = DEFAULT_CHARSET;
	
	CScreenDc ScreenDc;
	::SetMapMode (ScreenDc, MM_TEXT);
	pLogFont->lfHeight = -MulDiv (PointSize, GetDeviceCaps (ScreenDc, LOGPIXELSY), 72);
		
	ModifyLogFont (pLogFont, Flags);
	return true;
}

void
ModifyLogFont (
	LOGFONTW* pLogFont,
	uint_t Flags
	)
{
	pLogFont->lfWeight    = (Flags & EFontFlag_Bold) ? FW_BOLD : FW_NORMAL;
	pLogFont->lfItalic    = (Flags & EFontFlag_Italic) != 0;
	pLogFont->lfUnderline = (Flags & EFontFlag_Underline) != 0;
	pLogFont->lfStrikeOut = (Flags & EFontFlag_Strikeout) != 0;
}

bool
GetFontDescFromLogFont (
	const LOGFONT* pLogFont,
	TFontDesc* pFontDesc
	)
{
	memset (pFontDesc, 0, sizeof (TFontDesc));

	memcpy (
		pFontDesc->m_FaceName, 
		pLogFont->lfFaceName, 
		(AXL_MIN (countof (pLogFont->lfFaceName), countof (pFontDesc->m_FaceName)) - 1) * sizeof (char)
		);

	CScreenDc ScreenDc;
	::SetMapMode (ScreenDc, MM_TEXT);
	
	pFontDesc->m_PointSize = 
		pLogFont->lfHeight > 0 ? pLogFont->lfHeight :
		MulDiv (-pLogFont->lfHeight, 72, GetDeviceCaps (ScreenDc, LOGPIXELSY));

	if (pLogFont->lfWeight >= FW_BOLD)
		pFontDesc->m_Flags |= EFontFlag_Bold;

	if (pLogFont->lfItalic)
		pFontDesc->m_Flags |= EFontFlag_Italic;

	if (pLogFont->lfUnderline)
		pFontDesc->m_Flags |= EFontFlag_Underline;

	if (pLogFont->lfStrikeOut)
		pFontDesc->m_Flags |= EFontFlag_Strikeout;

	return true;
}

//.............................................................................

CFont::CFont ()
{
	m_pEngine = CEngine::GetSingleton ();
}

bool
CFont::GetLogFont (LOGFONTW* pLogFont)
{
	bool_t Result = ::GetObject (m_h, sizeof (LOGFONT), pLogFont);
	return err::Complete (Result);
}

bool
CFont::IsMonospace ()
{
	LOGFONT LogFont;
	GetLogFont (&LogFont);
	return LogFont.lfPitchAndFamily == FIXED_PITCH;
}

TSize
CFont::CalcTextSize (
	const char* pText,
	size_t Length
	)
{
	CScreenDc ScreenDc;
	HFONT hOldFont = (HFONT) ::SelectObject (ScreenDc, m_h);

	rtl::CString_w Text (pText, Length);

	SIZE Size;
	::GetTextExtentPoint32W (ScreenDc, Text, Text.GetLength (), &Size);
	::SelectObject (ScreenDc, hOldFont);

	return TSize (Size.cx, Size.cy);
}

//.............................................................................

} // namespace gdi
} // namespace gui
} // namespace axl