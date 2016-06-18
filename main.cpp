////////////////////////////////////////////////////////////////////////////////
// Filename: main.cpp
////////////////////////////////////////////////////////////////////////////////
#include "systemclass.h"
#include<d3d10.h>
#include<Windows.h>
//dsadsadasdsa
#pragma comment( lib, "d3d11.lib" )   // D3D11 라이브러리 
#pragma comment( lib, "d3dx11.lib" )
int myscore = 0;
std::wstring s2ws(const std::string s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}
LRESULT CALLBACK WndProc2(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    string sval = "점수 : ";
    sval+= to_string(myscore);
    sval += "점";
    int size = sval.length();
    wstring wval = s2ws(sval);
    LPCWSTR val = wval.c_str();
    HDC hdc = GetDC(hWnd);
	   TextOut(hdc, 0,30, val, size-3);
	   ReleaseDC(hWnd, hdc);

    return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
    HINSTANCE g_hInst;
    LPCWSTR lpszClass = TEXT("TextOut");
    HWND hWnd;
    MSG Message;
    WNDCLASS WndClass;
    g_hInst = hInstance;

    WndClass.cbClsExtra = 0;
    WndClass.cbWndExtra = 0;
    WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    WndClass.hInstance = hInstance;
    WndClass.lpfnWndProc = (WNDPROC)WndProc2;
    WndClass.lpszClassName = lpszClass;
    WndClass.lpszMenuName = NULL;
    WndClass.style = CS_HREDRAW | CS_VREDRAW;
    RegisterClass(&WndClass);
    hWnd = CreateWindow(lpszClass, TEXT("AA"), WS_OVERLAPPEDWINDOW, 560, 790, 800, 100, NULL, (HMENU)NULL, hInstance, NULL);

    ShowWindow(hWnd, iCmdshow);







	SystemClass* System;
	bool result;

	// Create the system object.
	System = new SystemClass;
	if (!System)
	{
		return 0;
	}

	// Initialize and run the system object.
	result = System->Initialize();
	if (result)
	{
		System->Run();
	}

	// Shutdown and release the system object.
	System->Shutdown();
	delete System;
	System = 0;

	return 0;
}