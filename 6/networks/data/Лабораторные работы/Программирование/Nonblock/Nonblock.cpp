// Nonblock.cpp : Defines the entry point for the application.

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <windows.h>
#include <winsock2.h>
#include <stdio.h>

#ifndef WINSOCK_VERSION
#define WINSOCK_VERSION 0x0202
#endif // WINSOCK_VERSION

#pragma warning ( disable: 4786 )
#include <string>
#include <list>
using namespace std;

#include "resource.h"

typedef list<string> StringList;
StringList g_List;

const char* CLASSNAME = "NONBLOCKSOCKET";
const short SERVERPORT = htons(5150);
const unsigned int UM_SOCKET_NOTIFICATION = WM_USER + 101;

void HandleError( int, char* );
bool InitInstance( HINSTANCE );
LRESULT CALLBACK MainWindowProc( HWND, UINT, WPARAM, LPARAM );
bool Startup( HWND );
bool Cleanup( HWND );
bool Listen ( HWND );
bool HandleSocketEvent( HWND, SOCKET, int);
bool AddToReport( HWND, char* );
void DrawLog( HDC );            

SOCKET g_ServerSocket;

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
    HWND hMainWnd;
    MSG msg;

    if (!InitInstance(hInstance)){
        // Failed
        HandleError(GetLastError(), "InitInstance");
    }

    hMainWnd = CreateWindow( CLASSNAME, "Non-blocking Socket sample", 
                             WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 
                             CW_USEDEFAULT, CW_USEDEFAULT, (HWND)NULL, 
                             (HMENU) NULL, hInstance, (LPVOID) NULL); 
    if (hMainWnd == NULL){
        HandleError(GetLastError(), "CreateWindow");
    }

    ShowWindow(hMainWnd, nCmdShow); 
    UpdateWindow(hMainWnd);     

    while (GetMessage(&msg, NULL, 0, 0) > 0)
    { 
        TranslateMessage(&msg); 
        DispatchMessage(&msg); 
    } 
    
    return msg.wParam;
}

void HandleError(int errcode, char* where)
{
    char strerr[255];
    sprintf(strerr, "Error has occured in %s.\nError code - %d", where, errcode);
    MessageBox(NULL, strerr, "Sample", MB_OK|MB_ICONERROR);
    PostQuitMessage(0);
}

bool InitInstance(HINSTANCE hInst)
{
    WNDCLASS wc;
    memset(&wc, 0, sizeof(wc));
    wc.hInstance = hInst;
    wc.hIcon = LoadIcon(NULL, IDI_ASTERISK);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpfnWndProc = MainWindowProc;
    wc.lpszClassName = CLASSNAME;
    wc.lpszMenuName = MAKEINTRESOURCE(IDR_MAINMENU);
    wc.style = CS_DBLCLKS|CS_HREDRAW|CS_VREDRAW;
    wc.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));

    return RegisterClass(&wc) != 0;
}

LRESULT CALLBACK MainWindowProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch( uMsg ){
        case WM_CLOSE:
            PostQuitMessage(0);
            break;
        case WM_COMMAND:
            switch(LOWORD(wParam)){
                case ID_FILEEXIT:
                    SendMessage( hwnd, WM_CLOSE, 0, 0 );
                    break;
                case ID_FILE_STARTUP:
                    Startup( hwnd );
                    break;
                case ID_FILE_CLEANUP:
                    Cleanup( hwnd );
                    break;
                case ID_FILE_LISTEN:
                    Listen( hwnd );
                    break;
                default:
                    break;
            }
            break;
        case UM_SOCKET_NOTIFICATION:
            HandleSocketEvent( hwnd, (SOCKET)wParam, WSAGETSELECTEVENT(lParam) );
            break;
        case WM_PAINT:
            PAINTSTRUCT pc;
            BeginPaint(hwnd, &pc);
            DrawLog(pc.hdc);            
            EndPaint(hwnd, &pc);
            break;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

bool Startup( HWND hwnd )
{
    WSADATA wsadata;
    int retcode = WSAStartup(WINSOCK_VERSION, &wsadata);
    
    if (retcode != 0){
        HandleError(retcode, "WSAStartup");
        return false;
    }
    AddToReport( hwnd, "Winsock initialized." );
    return true;
}

bool Cleanup( HWND hwnd )
{
    closesocket( g_ServerSocket );

    int retcode = WSACleanup();
    if (retcode != 0){
        // Failed
        HandleError(WSAGetLastError(), "WSACleanup");
        return false;
    }

    AddToReport( hwnd, "Winsock uninitialized." );
    return true;
}

bool Listen ( HWND hwnd )
{
    g_ServerSocket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
    if ( g_ServerSocket == INVALID_SOCKET ){
        HandleError( WSAGetLastError(), "socket" );
    }

    sockaddr_in sa;
    memset( &sa, 0, sizeof(sa) );
    sa.sin_family = AF_INET;
    sa.sin_port = SERVERPORT;
    sa.sin_addr.s_addr = INADDR_ANY;

    int retcode = bind( g_ServerSocket, (sockaddr*)&sa, sizeof(sa) );
    if ( retcode == SOCKET_ERROR ){
        HandleError( WSAGetLastError(), "bind" );
    }

    retcode = WSAAsyncSelect(g_ServerSocket, hwnd, UM_SOCKET_NOTIFICATION, 
                               FD_READ|FD_ACCEPT);
    if ( retcode == SOCKET_ERROR ){
        HandleError( WSAGetLastError(), "WSAAsyncSelect" );
    }

    retcode = listen(g_ServerSocket, 5);
    if ( retcode == SOCKET_ERROR ){
        HandleError( WSAGetLastError(), "listen" );
    }
    
    AddToReport( hwnd, "Listen..." );

    return true;
}

bool HandleSocketEvent( HWND hwnd, SOCKET s, int event )
{
    if (event == FD_ACCEPT){
        sockaddr_in sa;
        memset( &sa, 0, sizeof(sa) );
        int len = sizeof(sa);
        SOCKET newsocket = accept(g_ServerSocket, (sockaddr*)&sa, &len );
        if ( newsocket == INVALID_SOCKET ){
            HandleError( WSAGetLastError(), "accept" );
        }
        char data[255];
        sprintf(data, "Accepted connection from %s:%d", inet_ntoa(sa.sin_addr), ntohs(sa.sin_port) );
        AddToReport( hwnd, data );
    }

    if ( event == FD_READ ){
        char buffer[1024];
        char data[1024];
        memset( buffer, 0, 1024 );

        unsigned long cmd = 0;

        int bytesread = recv( s, buffer, 1024, 0 );
        if ( bytesread == SOCKET_ERROR ){
            HandleError( WSAGetLastError(), "recv" );
        }
        
        int bytessent = send( s, buffer, strlen(buffer), 0 );
        if ( bytessent == SOCKET_ERROR ){
            HandleError( WSAGetLastError(), "sent" );
        }

        sprintf(data, "Received: (%s). Sent: (%s)", buffer, buffer );
        AddToReport( hwnd, data );
    }

    return true;
}

bool AddToReport( HWND hwnd, char* data )
{
    g_List.push_back(data);
    RedrawWindow( hwnd, NULL, NULL, RDW_INVALIDATE);
    return true;
}
    
void DrawLog( HDC hdc )
{
    StringList::iterator it = g_List.begin();
    int posx = 5;
    int posy = 5;
    SIZE sz;
    GetTextExtentPoint32( hdc, "Text", strlen("Text"), &sz );
    for ( ; it != g_List.end(); ++it ){
        
        TextOut(hdc, posx, posy, (*it).c_str(), (*it).length() );
        posy += sz.cy + 3;
    }
}            
