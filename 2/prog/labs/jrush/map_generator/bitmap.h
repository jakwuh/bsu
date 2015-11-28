/**
* @author RJ TM
* @version 0.0.1
* @date 13.03.2015
*/

#ifndef __BITMAP_H_INCLUDED__
#define __BITMAP_H_INCLUDED__

#include "surface.h"
#include "map.h"
#include <Windows.h>
#include <iostream>

void generateBitmap(Map<Surface>, int, int, LPTSTR, int);
PBITMAPINFO CreateBitmapInfoStruct(HWND, HBITMAP);
void CreateBMPFile(HWND, LPTSTR, PBITMAPINFO, HBITMAP, HDC);
void errhandler(char*, HWND);

#endif