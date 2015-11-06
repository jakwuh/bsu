include windows.inc
include kernel32.inc
include user32.inc
include gdi32.inc
include comdlg32.inc

includelib user32.lib
includelib kernel32.lib
includelib comdlg32.lib
includelib gdi32.lib

WinMain proto :DWORD,:DWORD,:DWORD,:DWORD
DlgProc proto :DWORD,:DWORD,:DWORD,:DWORD


IDR_MENU				equ 10000
IDM_AUTHOR			equ 10007
IDM_LOAD_FILE		equ 10002
IDM_CHOOSE_COLOR	equ 10003
IDM_NUMBER			equ 10004
IDM_EXIT				equ 10005
IDD_DLG1				equ 1000
IDC_STC1				equ 1001
IDC_EDT1				equ 1002
IDC_BTN1				equ 1003
IDC_CHK1				equ 1004

.const
	ClassName		db "MainClasss",0
	AppName 			db "Main",0
	Author			db "James Akwuh", 0
	AuthorCaption	db "Author", 0

.data
	char				db 'a'
	len 				db 7
	part				db 100 dup (0)
	indent			dd 40
	checked  		db 0

.data?
	hInstance		HINSTANCE ?
	CommandLine		LPSTR ?
	
	rect				RECT <>
	ps					PAINTSTRUCT <>
	hdc				HDC <>
	
	ofn				OPENFILENAME <>
	buffer			db 100 dup (?)
	
	cc					CHOOSECOLOR <>
	custColors		COLORREF 16 dup(?)  
	hFontBrush		HBRUSH <>
	hBackBrush		HBRUSH <>   
	hEdit				dd ?
	
	chf				CHOOSEFONT <>
	lf					LOGFONT <>