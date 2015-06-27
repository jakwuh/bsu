#ifndef __CLIPBOARD_H_INCLUDED__
#define __CLIPBOARD_H_INCLUDED__

#include <Windows.h>
#include <string>;

class ClipBoard
{
public:
	friend ClipBoard& operator << (ClipBoard& cb, std::string const& s) {
		OpenClipboard(0);
		EmptyClipboard();
		HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, s.size());
		if (!hg){
			CloseClipboard();
			return cb;
		}
		memcpy(GlobalLock(hg), s.c_str(), s.size());
		GlobalUnlock(hg);
		SetClipboardData(CF_TEXT, hg);
		CloseClipboard();
		GlobalFree(hg);
		return cb;
	};
	friend ClipBoard& operator >> (ClipBoard& cb, std::string& s) {
		HANDLE clip;
		if (OpenClipboard(NULL)) {
			clip = GetClipboardData(CF_TEXT);
			s = std::string((char*)clip);
			CloseClipboard();
		}
		return cb;
	};
} ClipBoard;

#endif