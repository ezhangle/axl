#include "pch.h"
#include "axl_gui_Color.h"
#include "axl_rtl_ByteOrder.h"

namespace axl {
namespace gui {

//.............................................................................

static uint_t g_stdPalColorArray [StdPalColor__Count] =
{
	0, // EStdPalColor_Widget,
	0, // EStdPalColor_Text,
	0, // EStdPalColor_GrayText,
	0, // EStdPalColor_SelectionText,
	0, // EStdPalColor_SelectionBack,
	0, // EStdPalColor_3DFace,
	0, // EStdPalColor_3DShadow,
	0, // EStdPalColor_3DDarkShadow,
	0, // EStdPalColor_3DLight,
	0, // EStdPalColor_3DHiLight,

	StdColor_Black,
	StdColor_White,
	StdColor_Gray,
	StdColor_Red,
	StdColor_Green,
	StdColor_Blue,
	StdColor_Purple,
	StdColor_Cyan,
	StdColor_LightRed,
	StdColor_LightGreen,
	StdColor_LightBlue,
	StdColor_LightPurple,
	StdColor_LightCyan,
	StdColor_PastelGray,
	StdColor_PastelRed,
	StdColor_PastelOrange,
	StdColor_PastelYellow,
	StdColor_PastelGreen,
	StdColor_PastelCyan,
	StdColor_PastelBlue,
	StdColor_PastelPurple,
};

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

const uint_t*
getStdPalColorArray ()
{
	return g_stdPalColorArray;
}

void
updateStdPalSystemColors ()
{
#if (_AXL_ENV == AXL_ENV_WIN)
	g_stdPalColorArray [~ColorFlag_Index & StdPalColor_WidgetText]    = inverseRgb (::GetSysColor (COLOR_WINDOWTEXT));
	g_stdPalColorArray [~ColorFlag_Index & StdPalColor_WidgetBack]    = inverseRgb (::GetSysColor (COLOR_WINDOW));
	g_stdPalColorArray [~ColorFlag_Index & StdPalColor_GrayText]      = inverseRgb (::GetSysColor (COLOR_GRAYTEXT));
	g_stdPalColorArray [~ColorFlag_Index & StdPalColor_SelectionText] = inverseRgb (::GetSysColor (COLOR_HIGHLIGHTTEXT));
	g_stdPalColorArray [~ColorFlag_Index & StdPalColor_SelectionBack] = inverseRgb (::GetSysColor (COLOR_HIGHLIGHT));
	g_stdPalColorArray [~ColorFlag_Index & StdPalColor_3DFace]        = inverseRgb (::GetSysColor (COLOR_3DFACE));
	g_stdPalColorArray [~ColorFlag_Index & StdPalColor_3DShadow]      = inverseRgb (::GetSysColor (COLOR_3DSHADOW));
	g_stdPalColorArray [~ColorFlag_Index & StdPalColor_3DDarkShadow]  = inverseRgb (::GetSysColor (COLOR_3DDKSHADOW));
	g_stdPalColorArray [~ColorFlag_Index & StdPalColor_3DLight]       = inverseRgb (::GetSysColor (COLOR_3DLIGHT));
	g_stdPalColorArray [~ColorFlag_Index & StdPalColor_3DHiLight]     = inverseRgb (::GetSysColor (COLOR_3DHILIGHT));
#else
	g_stdPalColorArray [~ColorFlag_Index & StdPalColor_WidgetText]    = 0x000000;
	g_stdPalColorArray [~ColorFlag_Index & StdPalColor_WidgetBack]    = 0xffffff;
	g_stdPalColorArray [~ColorFlag_Index & StdPalColor_GrayText]      = 0x808080;
	g_stdPalColorArray [~ColorFlag_Index & StdPalColor_SelectionText] = 0xffffff;
	g_stdPalColorArray [~ColorFlag_Index & StdPalColor_SelectionBack] = 0x000080;
	g_stdPalColorArray [~ColorFlag_Index & StdPalColor_3DFace]        = 0xc0c0c0;
	g_stdPalColorArray [~ColorFlag_Index & StdPalColor_3DShadow]      = 0x808080;
	g_stdPalColorArray [~ColorFlag_Index & StdPalColor_3DDarkShadow]  = 0x000000;
	g_stdPalColorArray [~ColorFlag_Index & StdPalColor_3DLight]       = 0xe0e0e0;
	g_stdPalColorArray [~ColorFlag_Index & StdPalColor_3DHiLight]     = 0xffffff;
#endif
}

static
class InitStdPalSystemColors 
{
public:
	InitStdPalSystemColors ()
	{
		updateStdPalSystemColors ();
	}
} g_initStdColors;

//.............................................................................

uint_t
parseColorString (
	const char* string,
	const char** end_o
	)
{
	if (!string)
	{
		if (end_o)
			*end_o = NULL;

		return ColorFlag_Transparent;
	}

	uint_t color = ColorFlag_Transparent;

	char* end;

	if (string[0] == '#')
	{
		uint_t rgb = strtol (string + 1, &end, 16);
		if (end != string)
			color = rgb;
	}
	else
	{
		uint_t index = strtol (string, &end, 10);
		if (end != string)
			color = ColorFlag_Index | index;
	}

	if (end_o)
		*end_o = end;

	return color;
}

//.............................................................................

void
ColorAttr::parse (
	const char* string,
	const char** end
	)
{
	m_foreColor = parseColorString (string, &string);
	m_backColor = ColorFlag_Transparent;

	while (isspace (*string))
		string++;

	if (*string == '|')
		m_backColor = parseColorString (string + 1, &string);

	if (end)
		*end = string;
}

void
ColorAttr::parseOverlay (
	const ColorAttr& baseAttr,
	const char* string,
	const char** end
	)
{
	ColorAttr overlayAttr;
	overlayAttr.parse (string, end);
	overlay (baseAttr, overlayAttr);
}

//.............................................................................

} // namespace gui
} // namespace axl