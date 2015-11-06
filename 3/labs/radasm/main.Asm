.586
.model flat,stdcall
option casemap:none

include main.inc

.code

start:
	invoke GetModuleHandle, NULL
	mov    hInstance,eax
	
	invoke GetCommandLine
	mov    CommandLine,eax
	
	invoke WinMain, hInstance,NULL,CommandLine, SW_SHOWDEFAULT
	invoke ExitProcess,eax

WinMain proc hInst:HINSTANCE,hPrevInst:HINSTANCE,CmdLine:LPSTR,CmdShow:DWORD
	LOCAL wc:WNDCLASSEX
	LOCAL msg:MSG
	LOCAL hwnd:HWND
	
	mov wc.cbSize,SIZEOF WNDCLASSEX
	mov wc.style, CS_HREDRAW or CS_VREDRAW
	mov wc.lpfnWndProc, OFFSET WndProc
	mov wc.cbClsExtra,NULL
	mov wc.cbWndExtra,NULL
	mov eax,hInstance
	mov wc.hInstance,eax
	mov wc.hbrBackground,COLOR_BTNFACE+1
	mov wc.lpszMenuName,IDR_MENU
	mov wc.lpszClassName,OFFSET ClassName
	
	invoke LoadIcon,NULL,IDI_APPLICATION
	mov   wc.hIcon,eax
	mov   wc.hIconSm,eax
	
	invoke LoadCursor,NULL,IDC_ARROW
	mov   wc.hCursor,eax
	
	invoke RegisterClassEx, addr wc
	INVOKE CreateWindowEx,NULL,ADDR ClassName,ADDR AppName,\
		   WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,\
		   CW_USEDEFAULT,500,200,NULL,NULL,\
		   hInst,NULL
	mov   hwnd,eax
	
	invoke ShowWindow, hwnd,SW_SHOWNORMAL
	invoke UpdateWindow, hwnd
	
	.WHILE TRUE
		invoke GetMessage, ADDR msg,NULL,0,0
		.BREAK .IF (!eax)
		invoke TranslateMessage, ADDR msg
		invoke DispatchMessage, ADDR msg
	.ENDW
	
	mov eax,msg.wParam
	ret
WinMain endp

WndProc proc hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM
	
	.IF uMsg==WM_DESTROY
		invoke PostQuitMessage,NULL
	.ELSEIF uMsg==WM_CREATE
		invoke CreateSolidBrush, 000414141h
		mov hBackBrush, eax
		invoke CreateSolidBrush, 0
		mov hFontBrush, eax
		
		mov cc.lStructSize, sizeof(CHOOSECOLOR)
		push hInstance
		pop cc.hInstance
		mov cc.Flags, CC_RGBINIT
		mov cc.lpCustColors, offset custColors
		mov cc.hwndOwner, 0
		mov cc.rgbResult, 0000000h
		mov cc.lCustData, 0
		mov cc.lpfnHook, 0
		mov cc.lpTemplateName, 0
		
		mov ofn.lStructSize, sizeof ofn
		mov eax, hWnd
		mov ofn.hwndOwner, eax
		mov ofn.lpstrFile, offset buffer
		mov ofn.nMaxFile, sizeof buffer
		mov ofn.nFilterIndex, 1
		mov ofn.lpstrInitialDir, NULL
		mov ofn.Flags, OFN_PATHMUSTEXIST or OFN_FILEMUSTEXIST
		
	.ELSEIF uMsg==WM_COMMAND
		mov eax, wParam
		.IF eax==IDM_CHOOSE_COLOR
			invoke ChooseColor, addr cc
			.if eax != 0
				invoke DeleteObject, hFontBrush
				invoke CreateSolidBrush,cc.rgbResult
				mov hFontBrush, eax
				invoke InvalidateRect, hWnd, 0, 1
			.endif
		.ELSEIF eax==IDM_LOAD_FILE
			mov ecx, 99
			m1:
			mov [buffer + ecx], 0
			loop m1
			invoke GetOpenFileName,addr ofn
			.if eax == 1
				invoke InvalidateRect, hWnd, 0, 1
			.endif
		.ELSEIF eax==IDM_AUTHOR
			invoke MessageBox, hWnd, addr Author, addr AuthorCaption, MB_ICONASTERISK
		.ELSEIF eax==IDM_EXIT
			invoke SendMessage, hWnd, WM_CLOSE, NULL, NULL
		.ELSEIF eax==IDM_NUMBER
			invoke DialogBoxParam, hInstance, IDD_DLG1, hWnd, addr DlgProc, NULL 
			invoke InvalidateRect, hWnd, 0, 1
		.ENDIF
	.ELSEIF uMsg==WM_PAINT
		invoke BeginPaint, hWnd, addr ps
		mov hdc, eax
		invoke SetTextColor, hdc, cc.rgbResult
		invoke GetClientRect, hWnd, addr rect
		invoke SelectObject, hdc, hBackBrush      
		invoke Rectangle, hdc, 0, 0, rect.right, rect.bottom
		.if buffer[0]!= 0
			invoke SelectObject, hdc, hFontBrush
			invoke TextOut, hdc, 0, 0, addr buffer, 100
			
			mov edx, 0
			mov ecx, 0
			mov indent, 20;
			.while 1
				.if [buffer + ecx] == '\' || [buffer + ecx] == 0
					mov [part + edx], 0
					pushad
					.if dl >= len
						invoke TextOut, hdc, 0, indent, addr part, 100
						add indent, 20  
					.endif
					popad
					.while edx > 0
						mov [part + edx], 0
						dec edx
					.endw
					.if [buffer + ecx] == 0
						.break
					.endif
					xor edx, edx
				.else
					mov al, [buffer + ecx]
					mov [part + edx], al
					inc edx
				.endif
				inc ecx
			.endw       


		.endif
		invoke EndPaint, hWnd, addr ps
	.ELSE
		invoke DefWindowProc,hWnd,uMsg,wParam,lParam		
		ret
	.ENDIF
	
	mov eax, 0
	ret
WndProc endp

DlgProc proc hWin:HWND,uMsg:UINT,wParam:WPARAM,lParam:LPARAM
	mov		eax,uMsg
	.if eax==WM_INITDIALOG
		invoke  GetDlgItem, hWin, IDC_EDT1
		mov     hEdit, eax 
	.elseif eax==WM_COMMAND
		mov		eax,wParam
		.if eax==IDC_BTN1
			invoke SendMessage, hEdit, WM_GETTEXT, 2, addr char
			mov al, char
			sub al, 48
			mov len, al
			invoke EndDialog,hWin,0
		.endif
	.elseif eax==IDC_CHK1
		invoke SendMessage, hWin,BM_GETCHECK,0,0
		.if eax==BST_CHECKED
			mov edx, 1
		.else
			mov edx, 0
		.endif
		mov checked, dl
	.elseif eax==WM_SIZE
	.elseif eax==WM_CLOSE
		invoke EndDialog,hWin,1
	.elseif uMsg==WM_DESTROY
		invoke EndDialog,hWin,1
	ret
	.endif
	xor    eax,eax
	ret
DlgProc endp

end start
