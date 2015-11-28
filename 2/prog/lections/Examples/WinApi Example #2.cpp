LRESULT CALLBACK WndProc()
{
	static HWND hBUtton1, hButton2; // the next time function will be called the value of hButton1 remains the same
	switch(uMsg) {
		case WM_COMMAND: {
			switch (LOWORD(wparam)) {
				case ID_BUTTON1:
					MessageBox(hwnd, "Верхняя", "Сообщение от кнопки", MB_OK);
					SendMessage(HWND(lparam), BM_SETSTATE, TRUE, 0L);
					if (!SendMessage(hButton2, BM_GETCHECK, 0, 0L))
						SendMessage(HWND(hButton2), BM_SETSTATE, FALSE, 0L);
				case ID_BUTTON2:
					MessageBox(hwnd, "Нижняя", "Сообщение от кнопки", MB_OK);
					SendMessage(HWND(lparam), BM_SETSTATE, TRUE, 0L);
					if (!SendMessage(hButton1, BM_GETCHECK, 0, 0L))
						SendMessage(HWND(hButton1), BM_SETSTATE, FALSE, 0L);
			}
		}
	}
}