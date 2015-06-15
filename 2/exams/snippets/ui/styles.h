#ifndef __STYLES_H_INCLUDED__
#define __STYLES_H_INCLUDED__

#include <Windows.h>
#include <map>

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