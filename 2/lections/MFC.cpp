// Старое название MFC - afx

namespace Untitled
{
    void CMyView::OnChar(UINT nChar, UINT repCnt, UINT nFlags)
    {
    	CMyDoc* pDoc = GetDocument();
    	pDoc->StringData += nChar;
    	Invalidate();
    }

    void CMyView::OnDraw(CDC* pDC)
    {
    	pDc->TextOut(0, 0, pDoc->StringData);
    }
}

namespace ClassIerarchy
{
    CObject
    CCmdTarget, CFile, CDC, CGDIObject(Graphical device interface), CMenu
    |       |_______________________
    |       |_______                |
    CWnd            |           WinThread
    |               |               |
    CFrameWnd       |            CWinApp // Точка входа приложения MFC - конструктор CWinApp
                    CView
                    CDialog
                    CButton
                    CList
                    (...)
}

namespace Обработка сообщений
{
    Карта сообщений (Event map)
    DECLARE_MESSAGE_MAP(); // указывает соотношение событие - функция
    // В любом классе, который обрабатывает сообщения, должна быть EventsMap
    // Объявление карты
    BEGIN_MESSAGE_MAP(CMainWnd, [ CFrameWnd ]);
    /* ... */
    ON_WM_CHAR(); // макрос - расширяется в несколько строчек

    /* ... */
    END_MESSAGE_MAP();
    // Конец объявления
    namespace Основые сообщения {
        - Сообщения Windows
        - Сообщения от элементов
        - Командные сообщения
    }
}

namespace Untitled
{
    class CMainWnd : public CFrameWnd
    {
    public:
        CMainWnd();
        afx_msg void OnPaint();
        DECLARE_MESSAGE_MAP();
    };

    afx_msg void CMainWnd::OnPaint()
    {
        // чтобы рисовать необхдимо использовать объект CPaintDC(!)
        CPaintDC paintDC(this);
        paintDC.TextOut(25, 25, CString("Example"));
    }
}

namespace Ресурсы
{
    Хранящиеся независимые данные, находящиеся в конце .exe модуля, называются ресурсами.
    Ресурсы могут редактироваться независимо. Обычно не загружаются в память (только по запросу).
    Примеры :
        - Icon
        - Битовый образ (BitMap)
        - Cursors
        - Диалоги
        - Меню
    Для описания ресурсов существует специальный язык(.rc)
}

namespace Элементы управления
{
    push_button
    check_box
    radio_button
    listbox
    combobox
    editbox
}

