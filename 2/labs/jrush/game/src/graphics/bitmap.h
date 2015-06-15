/**
* @author James
* @version 0.0.1
* @date 13.03.2015
*/

#ifndef __BITMAP_H_INCLUDED__
#define __BITMAP_H_INCLUDED__

#include "..\config\surface.h"
#include "..\config\config.h"
#include "..\config\errors.h"
#include "..\includes\map.h"
#include <Windows.h>

void generateBitmap(Map<Surface>, int, int, LPTSTR);
PBITMAPINFO CreateBitmapInfoStruct(HWND, HBITMAP);
void CreateBMPFile(HWND, LPTSTR, PBITMAPINFO, HBITMAP, HDC);
void errhandler(char*, HWND);

#endif