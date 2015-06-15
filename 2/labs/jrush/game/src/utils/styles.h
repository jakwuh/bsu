#ifndef __COLORS_H_INCLUDED__
#define __COLORS_H_INCLUDED__

#include <Windows.h>
#include <map>
#include "..\core\interfaces.h"

using namespace types;

namespace colors
{
    static COLORREF black = RGB(0, 0, 0);
	static COLORREF white = RGB(255, 255, 255);
	static COLORREF gray = RGB(200, 200, 200);
    static COLORREF title_color = RGB(57,127,196);
	static COLORREF menu_background = RGB(149, 199, 171);

    static COLORREF default_color = RGB(240, 240, 240);
    static COLORREF color1 = RGB(255, 0, 0);
    static COLORREF color2 = RGB(0, 255, 0);
}

namespace pens
{
    static PenMap generatePenMap()
    {
        PenMap map;
        map["default"] = CreatePen(PS_SOLID, 1, ::colors::black);
		map["cursor"] = CreatePen(PS_SOLID, 10, ::colors::white);
		map["cursor_passive"] = CreatePen(PS_SOLID, 10, ::colors::gray);
        map["null"] = CreatePen(PS_NULL, 0, 0);
        return map;
    }

    static PenMap map = generatePenMap();
}

namespace brushes
{
    static BrushMap generateBrushMap()
    {
        BrushMap map;
        map[::colors::menu_background] = CreateSolidBrush(::colors::menu_background);
        map[::colors::color1] = CreateSolidBrush(::colors::color1);
        map[::colors::color2] = CreateSolidBrush(::colors::color2);
        map[::colors::default_color] = CreateSolidBrush(::colors::default_color);
        return map;
    }

    static BrushMap map = generateBrushMap();
}

namespace fonts
{
    static HFONT title_text = CreateFont(100, 0, 0, 0, FW_DONTCARE, /*italic*/ FALSE, 
    		/*underline*/ TRUE, /*strikeout*/ FALSE, DEFAULT_CHARSET, 
        OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, 
        VARIABLE_PITCH, TEXT("Impact"));
    
    static HFONT button_text = CreateFont(50, 0, 0, 0, FW_DONTCARE, /*italic*/ FALSE, 
            /*underline*/ FALSE, /*strikeout*/ FALSE, DEFAULT_CHARSET, 
        OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, 
        VARIABLE_PITCH, TEXT("Impact"));

    static HFONT status_text = CreateFont(18, 0, 0, 0, FW_DONTCARE, /*italic*/ FALSE, 
            /*underline*/ FALSE, /*strikeout*/ FALSE, DEFAULT_CHARSET, 
        OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, 
        VARIABLE_PITCH, TEXT("Impact"));

    static HFONT town_text = CreateFont(20, 0, 0, 0, FW_DONTCARE, /*italic*/ FALSE, 
            /*underline*/ FALSE, /*strikeout*/ FALSE, DEFAULT_CHARSET, 
        OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, 
        VARIABLE_PITCH, TEXT("Impact"));
}

#endif