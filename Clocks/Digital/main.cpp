#include <windows.h>
#include <math.h>
#include <cmath>
#include<stdlib.h>
#include <wchar.h>

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,PSTR szCmdLine, int iCmdShow)
{
    static char szAppName[] = "SineWave" ;
	HWND        hwnd ;
	MSG         msg ;
	WNDCLASSEX  wndclass;
	
	SYSTEMTIME lt = {0};
    GetLocalTime(&lt);
	
	wndclass.cbSize        = sizeof (wndclass) ;
	wndclass.style         = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc   = WndProc ;
	wndclass.cbClsExtra    = 0 ;
	wndclass.cbWndExtra    = 0 ;
	wndclass.hInstance     = hInstance ;
	wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;
	wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
	wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
	wndclass.lpszMenuName  = NULL ;
	wndclass.lpszClassName = szAppName ;
	wndclass.hIconSm       = LoadIcon (NULL, IDI_APPLICATION) ;
	RegisterClassEx (&wndclass) ;
	hwnd = CreateWindow (szAppName, "Clock",
	              WS_OVERLAPPEDWINDOW,
	              50, 50,
	              1300, 600,
	              NULL, NULL, hInstance, NULL) ;
	
	ShowWindow (hwnd, iCmdShow) ;
	UpdateWindow (hwnd) ;
	SetTimer(hwnd, 0, 1000, NULL);
	
	while (GetMessage (&msg, NULL, 0, 0))
	{
		TranslateMessage (&msg) ;
		DispatchMessage (&msg) ;
	}
	
	return msg.wParam ;
}
    
LRESULT CALLBACK WndProc (HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    static int  cxClient, cyClient;
    static int i = 0;
	HDC         hdc;
	PAINTSTRUCT ps;
	
	SYSTEMTIME lt;
    GetLocalTime(&lt);
	
	int zsec = lt.wSecond / 10, usec = lt.wSecond % 10;
    int zmin = lt.wMinute / 10, umin = lt.wMinute % 10;
	int zh = lt.wHour / 10, uh = lt.wHour % 10;
	
	HPEN pen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
//	HBRUSH inside = CreateSolidBrush(RGB(148,163,229));
	HBRUSH inside = CreateSolidBrush(RGB(154,157,144));
//	HBRUSH inside = CreateSolidBrush(RGB(0,0,0));
//	HBRUSH inside = CreateSolidBrush(RGB(255,255,255));
//	HPEN pen = CreatePen(PS_SOLID, 3, RGB(255,255,255));
	HBRUSH red = CreateSolidBrush(RGB(255, 0, 0));
	HPEN white = CreatePen(PS_SOLID, 3, RGB(255,255,255));
	HBRUSH brwhite = CreateSolidBrush(RGB(255,255,255));
	HPEN penred = CreatePen(PS_SOLID, 0, RGB(255, 0, 0));

	int xzh = -400-100;
	int xuh = -250-100;
	int xzm = -70-100;
	int xum = 80-100;
	int xzs = 260-100;
	int xus = 410-100;
	int y = -110;

	POINT azh[] = 
	{
		cxClient/2+xzh, cyClient/2+y,
		cxClient/2 + 120+xzh, cyClient/2+y,
		(cxClient/2 + 120)+15*sin(5*M_PI/4)+xzh, cyClient/2-15*cos(5*M_PI/4)+y,
		cxClient/2-15*sin(5*M_PI/4)+xzh, cyClient/2-15*cos(5*M_PI/4)+y,
		cxClient/2+xzh, cyClient/2+y
	};
	
	POINT bzh[] = 
	{
		cxClient/2+124+xzh, cyClient/2+2+y,
		cxClient/2+124+xzh, cyClient/2+100+y,
		(cxClient/2+124)+7*sin(5*M_PI/4)+xzh, (cyClient/2+100)-7*sin(5*M_PI/4)+y,
		cxClient/2+113+xzh, cyClient/2+99+y,
		(cxClient/2+124)+15*sin(5*M_PI/4)+xzh, (cyClient/2+2)-15*sin(5*M_PI/4)+y,
		cxClient/2+124+xzh, cyClient/2+2+y
	};

	POINT czh[] = 
	{
		cxClient/2+114+xzh, cyClient/2+113+y,
		cxClient/2+114+xzh, cyClient/2+201+y,
		cxClient/2-16*sin(5*M_PI/4)+114+xzh, cyClient/2-16*cos(5*M_PI/4)+201+y,
		cxClient/2+125+xzh, cyClient/2+113+y,
		(cxClient/2+125)+7*sin(5*M_PI/4)+xzh, cyClient/2+7*cos(5*M_PI/4)+113+y,
		cxClient/2+114+xzh, cyClient/2+113+y
	};

	POINT dzh[] = 
	{
		cxClient/2+xzh, cyClient/2+214+y,
		cxClient/2 + 120+xzh, cyClient/2+214+y,
		(cxClient/2 + 120)+13*sin(5*M_PI/4)+xzh, cyClient/2+13*cos(5*M_PI/4)+214+y,
		cxClient/2-13*sin(5*M_PI/4)+xzh, cyClient/2+13*cos(5*M_PI/4)+214+y,
		cxClient/2+xzh, cyClient/2+214+y
	};
	
	POINT ezh[] = 
	{
		cxClient/2-5+xzh, cyClient/2+113+y,
		cxClient/2-5+xzh, cyClient/2+212+y,
		cxClient/2-16*sin(5*M_PI/4)-5+xzh, cyClient/2+16*cos(5*M_PI/4)+213+y,
		cxClient/2+6+xzh, cyClient/2+113+y,
		(cxClient/2+6)+7*sin(5*M_PI/4)+xzh, cyClient/2+7*cos(5*M_PI/4)+113+y,
		cxClient/2-5+xzh, cyClient/2+113+y
	};
	
	POINT fzh[] = 
	{
		(cxClient/2-4)-15*sin(5*M_PI/4)+xzh, (cyClient/2+2)-15*sin(5*M_PI/4)+y,
		cxClient/2- 4+xzh, cyClient/2+2+y,
		cxClient/2-4+xzh, cyClient/2+100+y,
		(cxClient/2+6)+7*sin(5*M_PI/4)+xzh, (cyClient/2+100)-7*sin(5*M_PI/4)+y,
		cxClient/2+6+xzh, cyClient/2+99+y,
		(cxClient/2-4)-15*sin(5*M_PI/4)+xzh, (cyClient/2+2)-15*sin(5*M_PI/4)+y
	};
	
	POINT gzh[] = 
	{
		cxClient/2+12+xzh, cyClient/2+99+y,
		(cxClient/2+12)+8*sin(5*M_PI/4)+xzh, cyClient/2+99-8*cos(5*M_PI/4)+y,
		cxClient/2+12+xzh, cyClient/2+110+y,
		cxClient/2 + 108+xzh, cyClient/2+110+y,
		(cxClient/2+108)-8*sin(5*M_PI/4)+xzh, cyClient/2+110+8*cos(5*M_PI/4)+y,
		cxClient/2+108+xzh, cyClient/2+99+y,
		cxClient/2+12+xzh, cyClient/2+99+y
	};

 POINT auh[] = 
	{
		cxClient/2+xuh, cyClient/2+y,
		cxClient/2 + 120+xuh, cyClient/2+y,
		(cxClient/2 + 120)+15*sin(5*M_PI/4)+xuh, cyClient/2-15*cos(5*M_PI/4)+y,
		cxClient/2-15*sin(5*M_PI/4)+xuh, cyClient/2-15*cos(5*M_PI/4)+y,
		cxClient/2+xuh, cyClient/2+y
	};
	
	POINT buh[] = 
	{
		cxClient/2+124+xuh, cyClient/2+2+y,
		cxClient/2+124+xuh, cyClient/2+100+y,
		(cxClient/2+124)+7*sin(5*M_PI/4)+xuh, (cyClient/2+100)-7*sin(5*M_PI/4)+y,
		cxClient/2+113+xuh, cyClient/2+99+y,
		(cxClient/2+124)+15*sin(5*M_PI/4)+xuh, (cyClient/2+2)-15*sin(5*M_PI/4)+y,
		cxClient/2+124+xuh, cyClient/2+2+y
	};

	POINT cuh[] = 
	{
		cxClient/2+114+xuh, cyClient/2+113+y,
		cxClient/2+114+xuh, cyClient/2+201+y,
		cxClient/2-16*sin(5*M_PI/4)+114+xuh, cyClient/2-16*cos(5*M_PI/4)+201+y,
		cxClient/2+125+xuh, cyClient/2+113+y,
		(cxClient/2+125)+7*sin(5*M_PI/4)+xuh, cyClient/2+7*cos(5*M_PI/4)+113+y,
		cxClient/2+114+xuh, cyClient/2+113+y
	};

	POINT duh[] = 
	{
		cxClient/2+xuh, cyClient/2+214+y,
		cxClient/2 + 120+xuh, cyClient/2+214+y,
		(cxClient/2 + 120)+13*sin(5*M_PI/4)+xuh, cyClient/2+13*cos(5*M_PI/4)+214+y,
		cxClient/2-13*sin(5*M_PI/4)+xuh, cyClient/2+13*cos(5*M_PI/4)+214+y,
		cxClient/2+xuh, cyClient/2+214+y
	};
	
	POINT euh[] = 
	{
		cxClient/2-5+xuh, cyClient/2+113+y,
		cxClient/2-5+xuh, cyClient/2+212+y,
		cxClient/2-16*sin(5*M_PI/4)-5+xuh, cyClient/2+16*cos(5*M_PI/4)+213+y,
		cxClient/2+6+xuh, cyClient/2+113+y,
		(cxClient/2+6)+7*sin(5*M_PI/4)+xuh, cyClient/2+7*cos(5*M_PI/4)+113+y,
		cxClient/2-5+xuh, cyClient/2+113+y
	};
	
	POINT fuh[] = 
	{
		(cxClient/2-4)-15*sin(5*M_PI/4)+xuh, (cyClient/2+2)-15*sin(5*M_PI/4)+y,
		cxClient/2- 4+xuh, cyClient/2+2+y,
		cxClient/2-4+xuh, cyClient/2+100+y,
		(cxClient/2+6)+7*sin(5*M_PI/4)+xuh, (cyClient/2+100)-7*sin(5*M_PI/4)+y,
		cxClient/2+6+xuh, cyClient/2+99+y,
		(cxClient/2-4)-15*sin(5*M_PI/4)+xuh, (cyClient/2+2)-15*sin(5*M_PI/4)+y
	};
	
	POINT guh[] = 
	{
		cxClient/2+12+xuh, cyClient/2+99+y,
		(cxClient/2+12)+8*sin(5*M_PI/4)+xuh, cyClient/2+99-8*cos(5*M_PI/4)+y,
		cxClient/2+12+xuh, cyClient/2+110+y,
		cxClient/2 + 108+xuh, cyClient/2+110+y,
		(cxClient/2+108)-8*sin(5*M_PI/4)+xuh, cyClient/2+110+8*cos(5*M_PI/4)+y,
		cxClient/2+108+xuh, cyClient/2+99+y,
		cxClient/2+12+xuh, cyClient/2+99+y
	};


	POINT azm[] = 
	{
		cxClient/2+xzm, cyClient/2+y,
		cxClient/2 + 120+xzm, cyClient/2+y,
		(cxClient/2 + 120)+15*sin(5*M_PI/4)+xzm, cyClient/2-15*cos(5*M_PI/4)+y,
		cxClient/2-15*sin(5*M_PI/4)+xzm, cyClient/2-15*cos(5*M_PI/4)+y,
		cxClient/2+xzm, cyClient/2+y
	};
	
	POINT bzm[] = 
	{
		cxClient/2+124+xzm, cyClient/2+2+y,
		cxClient/2+124+xzm, cyClient/2+100+y,
		(cxClient/2+124)+7*sin(5*M_PI/4)+xzm, (cyClient/2+100)-7*sin(5*M_PI/4)+y,
		cxClient/2+113+xzm, cyClient/2+99+y,
		(cxClient/2+124)+15*sin(5*M_PI/4)+xzm, (cyClient/2+2)-15*sin(5*M_PI/4)+y,
		cxClient/2+124+xzm, cyClient/2+2+y
	};

	POINT czm[] = 
	{
		cxClient/2+114+xzm, cyClient/2+113+y,
		cxClient/2+114+xzm, cyClient/2+201+y,
		cxClient/2-16*sin(5*M_PI/4)+114+xzm, cyClient/2-16*cos(5*M_PI/4)+201+y,
		cxClient/2+125+xzm, cyClient/2+113+y,
		(cxClient/2+125)+7*sin(5*M_PI/4)+xzm, cyClient/2+7*cos(5*M_PI/4)+113+y,
		cxClient/2+114+xzm, cyClient/2+113+y
	};

	POINT dzm[] = 
	{
		cxClient/2+xzm, cyClient/2+214+y,
		cxClient/2 + 120+xzm, cyClient/2+214+y,
		(cxClient/2 + 120)+13*sin(5*M_PI/4)+xzm, cyClient/2+13*cos(5*M_PI/4)+214+y,
		cxClient/2-13*sin(5*M_PI/4)+xzm, cyClient/2+13*cos(5*M_PI/4)+214+y,
		cxClient/2+xzm, cyClient/2+214+y
	};
	
	POINT ezm[] = 
	{
		cxClient/2-5+xzm, cyClient/2+113+y,
		cxClient/2-5+xzm, cyClient/2+212+y,
		cxClient/2-16*sin(5*M_PI/4)-5+xzm, cyClient/2+16*cos(5*M_PI/4)+213+y,
		cxClient/2+6+xzm, cyClient/2+113+y,
		(cxClient/2+6)+7*sin(5*M_PI/4)+xzm, cyClient/2+7*cos(5*M_PI/4)+113+y,
		cxClient/2-5+xzm, cyClient/2+113+y
	};
	
	POINT fzm[] = 
	{
		(cxClient/2-4)-15*sin(5*M_PI/4)+xzm, (cyClient/2+2)-15*sin(5*M_PI/4)+y,
		cxClient/2- 4+xzm, cyClient/2+2+y,
		cxClient/2-4+xzm, cyClient/2+100+y,
		(cxClient/2+6)+7*sin(5*M_PI/4)+xzm, (cyClient/2+100)-7*sin(5*M_PI/4)+y,
		cxClient/2+6+xzm, cyClient/2+99+y,
		(cxClient/2-4)-15*sin(5*M_PI/4)+xzm, (cyClient/2+2)-15*sin(5*M_PI/4)+y
	};
	
	POINT gzm[] = 
	{
		cxClient/2+12+xzm, cyClient/2+99+y,
		(cxClient/2+12)+8*sin(5*M_PI/4)+xzm, cyClient/2+99-8*cos(5*M_PI/4)+y,
		cxClient/2+12+xzm, cyClient/2+110+y,
		cxClient/2 + 108+xzm, cyClient/2+110+y,
		(cxClient/2+108)-8*sin(5*M_PI/4)+xzm, cyClient/2+110+8*cos(5*M_PI/4)+y,
		cxClient/2+108+xzm, cyClient/2+99+y,
		cxClient/2+12+xzm, cyClient/2+99+y
	};

	POINT aum[] = 
	{
		cxClient/2+xum, cyClient/2+y,
		cxClient/2 + 120+xum, cyClient/2+y,
		(cxClient/2 + 120)+15*sin(5*M_PI/4)+xum, cyClient/2-15*cos(5*M_PI/4)+y,
		cxClient/2-15*sin(5*M_PI/4)+xum, cyClient/2-15*cos(5*M_PI/4)+y,
		cxClient/2+xum, cyClient/2+y
	};
	
	POINT bum[] = 
	{
		cxClient/2+124+xum, cyClient/2+2+y,
		cxClient/2+124+xum, cyClient/2+100+y,
		(cxClient/2+124)+7*sin(5*M_PI/4)+xum, (cyClient/2+100)-7*sin(5*M_PI/4)+y,
		cxClient/2+113+xum, cyClient/2+99+y,
		(cxClient/2+124)+15*sin(5*M_PI/4)+xum, (cyClient/2+2)-15*sin(5*M_PI/4)+y,
		cxClient/2+124+xum, cyClient/2+2+y
	};

	POINT cum[] = 
	{
		cxClient/2+114+xum, cyClient/2+113+y,
		cxClient/2+114+xum, cyClient/2+201+y,
		cxClient/2-16*sin(5*M_PI/4)+114+xum, cyClient/2-16*cos(5*M_PI/4)+201+y,
		cxClient/2+125+xum, cyClient/2+113+y,
		(cxClient/2+125)+7*sin(5*M_PI/4)+xum, cyClient/2+7*cos(5*M_PI/4)+113+y,
		cxClient/2+114+xum, cyClient/2+113+y
	};

	POINT dum[] = 
	{
		cxClient/2+xum, cyClient/2+214+y,
		cxClient/2 + 120+xum, cyClient/2+214+y,
		(cxClient/2 + 120)+13*sin(5*M_PI/4)+xum, cyClient/2+13*cos(5*M_PI/4)+214+y,
		cxClient/2-13*sin(5*M_PI/4)+xum, cyClient/2+13*cos(5*M_PI/4)+214+y,
		cxClient/2+xum, cyClient/2+214+y
	};
	
	POINT eum[] = 
	{
		cxClient/2-5+xum, cyClient/2+113+y,
		cxClient/2-5+xum, cyClient/2+212+y,
		cxClient/2-16*sin(5*M_PI/4)-5+xum, cyClient/2+16*cos(5*M_PI/4)+213+y,
		cxClient/2+6+xum, cyClient/2+113+y,
		(cxClient/2+6)+7*sin(5*M_PI/4)+xum, cyClient/2+7*cos(5*M_PI/4)+113+y,
		cxClient/2-5+xum, cyClient/2+113+y
	};
	
	POINT fum[] = 
	{
		(cxClient/2-4)-15*sin(5*M_PI/4)+xum, (cyClient/2+2)-15*sin(5*M_PI/4)+y,
		cxClient/2- 4+xum, cyClient/2+2+y,
		cxClient/2-4+xum, cyClient/2+100+y,
		(cxClient/2+6)+7*sin(5*M_PI/4)+xum, (cyClient/2+100)-7*sin(5*M_PI/4)+y,
		cxClient/2+6+xum, cyClient/2+99+y,
		(cxClient/2-4)-15*sin(5*M_PI/4)+xum, (cyClient/2+2)-15*sin(5*M_PI/4)+y
	};
	
	POINT gum[] = 
	{
		cxClient/2+12+xum, cyClient/2+99+y,
		(cxClient/2+12)+8*sin(5*M_PI/4)+xum, cyClient/2+99-8*cos(5*M_PI/4)+y,
		cxClient/2+12+xum, cyClient/2+110+y,
		cxClient/2 + 108+xum, cyClient/2+110+y,
		(cxClient/2+108)-8*sin(5*M_PI/4)+xum, cyClient/2+110+8*cos(5*M_PI/4)+y,
		cxClient/2+108+xum, cyClient/2+99+y,
		cxClient/2+12+xum, cyClient/2+99+y
	};

	POINT azs[] = 
	{
		cxClient/2+xzs, cyClient/2+y,
		cxClient/2 + 120+xzs, cyClient/2+y,
		(cxClient/2 + 120)+15*sin(5*M_PI/4)+xzs, cyClient/2-15*cos(5*M_PI/4)+y,
		cxClient/2-15*sin(5*M_PI/4)+xzs, cyClient/2-15*cos(5*M_PI/4)+y,
		cxClient/2+xzs, cyClient/2+y
	};
	
	POINT bzs[] = 
	{
		cxClient/2+124+xzs, cyClient/2+2+y,
		cxClient/2+124+xzs, cyClient/2+100+y,
		(cxClient/2+124)+7*sin(5*M_PI/4)+xzs, (cyClient/2+100)-7*sin(5*M_PI/4)+y,
		cxClient/2+113+xzs, cyClient/2+99+y,
		(cxClient/2+124)+15*sin(5*M_PI/4)+xzs, (cyClient/2+2)-15*sin(5*M_PI/4)+y,
		cxClient/2+124+xzs, cyClient/2+2+y
	};

	POINT czs[] = 
	{
		cxClient/2+114+xzs, cyClient/2+113+y,
		cxClient/2+114+xzs, cyClient/2+201+y,
		cxClient/2-16*sin(5*M_PI/4)+114+xzs, cyClient/2-16*cos(5*M_PI/4)+201+y,
		cxClient/2+125+xzs, cyClient/2+113+y,
		(cxClient/2+125)+7*sin(5*M_PI/4)+xzs, cyClient/2+7*cos(5*M_PI/4)+113+y,
		cxClient/2+114+xzs, cyClient/2+113+y
	};

	POINT dzs[] = 
	{
		cxClient/2+xzs, cyClient/2+214+y,
		cxClient/2 + 120+xzs, cyClient/2+214+y,
		(cxClient/2 + 120)+13*sin(5*M_PI/4)+xzs, cyClient/2+13*cos(5*M_PI/4)+214+y,
		cxClient/2-13*sin(5*M_PI/4)+xzs, cyClient/2+13*cos(5*M_PI/4)+214+y,
		cxClient/2+xzs, cyClient/2+214+y
	};
	
	POINT ezs[] = 
	{
		cxClient/2-5+xzs, cyClient/2+113+y,
		cxClient/2-5+xzs, cyClient/2+212+y,
		cxClient/2-16*sin(5*M_PI/4)-5+xzs, cyClient/2+16*cos(5*M_PI/4)+213+y,
		cxClient/2+6+xzs, cyClient/2+113+y,
		(cxClient/2+6)+7*sin(5*M_PI/4)+xzs, cyClient/2+7*cos(5*M_PI/4)+113+y,
		cxClient/2-5+xzs, cyClient/2+113+y
	};
	
	POINT fzs[] = 
	{
		(cxClient/2-4)-15*sin(5*M_PI/4)+xzs, (cyClient/2+2)-15*sin(5*M_PI/4)+y,
		cxClient/2- 4+xzs, cyClient/2+2+y,
		cxClient/2-4+xzs, cyClient/2+100+y,
		(cxClient/2+6)+7*sin(5*M_PI/4)+xzs, (cyClient/2+100)-7*sin(5*M_PI/4)+y,
		cxClient/2+6+xzs, cyClient/2+99+y,
		(cxClient/2-4)-15*sin(5*M_PI/4)+xzs, (cyClient/2+2)-15*sin(5*M_PI/4)+y
	};
	
	POINT gzs[] = 
	{
		cxClient/2+12+xzs, cyClient/2+99+y,
		(cxClient/2+12)+8*sin(5*M_PI/4)+xzs, cyClient/2+99-8*cos(5*M_PI/4)+y,
		cxClient/2+12+xzs, cyClient/2+110+y,
		cxClient/2 + 108+xzs, cyClient/2+110+y,
		(cxClient/2+108)-8*sin(5*M_PI/4)+xzs, cyClient/2+110+8*cos(5*M_PI/4)+y,
		cxClient/2+108+xzs, cyClient/2+99+y,
		cxClient/2+12+xzs, cyClient/2+99+y
	};
	
	POINT aus[] = 
	{
		cxClient/2+xus, cyClient/2+y,
		cxClient/2 + 120+xus, cyClient/2+y,
		(cxClient/2 + 120)+15*sin(5*M_PI/4)+xus, cyClient/2-15*cos(5*M_PI/4)+y,
		cxClient/2-15*sin(5*M_PI/4)+xus, cyClient/2-15*cos(5*M_PI/4)+y,
		cxClient/2+xus, cyClient/2+y
	};
	
	POINT bus[] = 
	{
		cxClient/2+124+xus, cyClient/2+2+y,
		cxClient/2+124+xus, cyClient/2+100+y,
		(cxClient/2+124)+7*sin(5*M_PI/4)+xus, (cyClient/2+100)-7*sin(5*M_PI/4)+y,
		cxClient/2+113+xus, cyClient/2+99+y,
		(cxClient/2+124)+15*sin(5*M_PI/4)+xus, (cyClient/2+2)-15*sin(5*M_PI/4)+y,
		cxClient/2+124+xus, cyClient/2+2+y
	};

	POINT cus[] = 
	{
		cxClient/2+114+xus, cyClient/2+113+y,
		cxClient/2+114+xus, cyClient/2+201+y,
		cxClient/2-16*sin(5*M_PI/4)+114+xus, cyClient/2-16*cos(5*M_PI/4)+201+y,
		cxClient/2+125+xus, cyClient/2+113+y,
		(cxClient/2+125)+7*sin(5*M_PI/4)+xus, cyClient/2+7*cos(5*M_PI/4)+113+y,
		cxClient/2+114+xus, cyClient/2+113+y
	};

	POINT dus[] = 
	{
		cxClient/2+xus, cyClient/2+214+y,
		cxClient/2 + 120+xus, cyClient/2+214+y,
		(cxClient/2 + 120)+13*sin(5*M_PI/4)+xus, cyClient/2+13*cos(5*M_PI/4)+214+y,
		cxClient/2-13*sin(5*M_PI/4)+xus, cyClient/2+13*cos(5*M_PI/4)+214+y,
		cxClient/2+xus, cyClient/2+214+y
	};
	
	POINT eus[] = 
	{
		cxClient/2-5+xus, cyClient/2+113+y,
		cxClient/2-5+xus, cyClient/2+212+y,
		cxClient/2-16*sin(5*M_PI/4)-5+xus, cyClient/2+16*cos(5*M_PI/4)+213+y,
		cxClient/2+6+xus, cyClient/2+113+y,
		(cxClient/2+6)+7*sin(5*M_PI/4)+xus, cyClient/2+7*cos(5*M_PI/4)+113+y,
		cxClient/2-5+xus, cyClient/2+113+y
	};
	
	POINT fus[] = 
	{
		(cxClient/2-4)-15*sin(5*M_PI/4)+xus, (cyClient/2+2)-15*sin(5*M_PI/4)+y,
		cxClient/2- 4+xus, cyClient/2+2+y,
		cxClient/2-4+xus, cyClient/2+100+y,
		(cxClient/2+6)+7*sin(5*M_PI/4)+xus, (cyClient/2+100)-7*sin(5*M_PI/4)+y,
		cxClient/2+6+xus, cyClient/2+99+y,
		(cxClient/2-4)-15*sin(5*M_PI/4)+xus, (cyClient/2+2)-15*sin(5*M_PI/4)+y
	};
	
	POINT gus[] = 
	{
		cxClient/2+12+xus, cyClient/2+99+y,
		(cxClient/2+12)+8*sin(5*M_PI/4)+xus, cyClient/2+99-8*cos(5*M_PI/4)+y,
		cxClient/2+12+xus, cyClient/2+110+y,
		cxClient/2 + 108+xus, cyClient/2+110+y,
		(cxClient/2+108)-8*sin(5*M_PI/4)+xus, cyClient/2+110+8*cos(5*M_PI/4)+y,
		cxClient/2+108+xus, cyClient/2+99+y,
		cxClient/2+12+xus, cyClient/2+99+y
	};
	
	switch (iMsg)
	{
		case WM_SIZE:
		{
			cxClient = LOWORD (lParam);
			cyClient = HIWORD (lParam);
			return 0;
		}

        break;
	
		case WM_PAINT:
		{
			hdc = BeginPaint(hwnd, &ps);
			SelectObject(hdc, pen);
//			SelectObject(hdc, white);
			SelectObject(hdc, inside);
			
		
			Polygon(hdc, azh, 5);
			Polygon(hdc, bzh, 6);
			Polygon(hdc, czh, 6);
			Polygon(hdc, dzh, 5);
			Polygon(hdc, ezh, 6);
			Polygon(hdc, fzh, 6);
			Polygon(hdc, gzh, 7);
			
			Polygon(hdc, auh, 5);
			Polygon(hdc, buh, 6);
			Polygon(hdc, cuh, 6);
			Polygon(hdc, duh, 5);
			Polygon(hdc, euh, 6);
			Polygon(hdc, fuh, 6);
			Polygon(hdc, guh, 7);
			
			Polygon(hdc, azm, 5);
			Polygon(hdc, bzm, 6);
			Polygon(hdc, czm, 6);
			Polygon(hdc, dzm, 5);
			Polygon(hdc, ezm, 6);
			Polygon(hdc, fzm, 6);
			Polygon(hdc, gzm, 7);
			
			Polygon(hdc, aum, 5);
			Polygon(hdc, bum, 6);
			Polygon(hdc, cum, 6);
			Polygon(hdc, dum, 5);
			Polygon(hdc, eum, 6);
			Polygon(hdc, fum, 6);
			Polygon(hdc, gum, 7);
			
			Polygon(hdc, azs, 5);
			Polygon(hdc, bzs, 6);
			Polygon(hdc, czs, 6);
			Polygon(hdc, dzs, 5);
			Polygon(hdc, ezs, 6);
			Polygon(hdc, fzs, 6);
			Polygon(hdc, gzs, 7);
			
			Polygon(hdc, aus, 5);
			Polygon(hdc, bus, 6);
			Polygon(hdc, cus, 6);
			Polygon(hdc, dus, 5);
			Polygon(hdc, eus, 6);
			Polygon(hdc, fus, 6);
			Polygon(hdc, gus, 7);
			
//			SelectObject(hdc, inside);
//			SelectObject(hdc, white);
//			Ellipse(hdc, 405-10, 220-10,405+10, 220+10);
//			Ellipse(hdc, 405-10, 260-10,405+10, 260+10);
//			Ellipse(hdc, 735-10, 220-10,735+10, 220+10);
//			Ellipse(hdc, 735-10, 260-10,735+10, 260+10);			
//			SelectObject(hdc, pen);
			
			SelectObject(hdc, red);
			
			switch(zh){
				case 1: {
					Polygon(hdc, bzh, 6);
					Polygon(hdc, czh, 6);
					break;
				}
				case 2: {
					Polygon(hdc, azh, 5);
					Polygon(hdc, bzh, 6);
					Polygon(hdc, gzh, 7);
					Polygon(hdc, dzh, 5);
					Polygon(hdc, ezh, 6);
					break;
				}
				case 0:{
					Polygon(hdc, azh, 5);
					Polygon(hdc, bzh, 6);
					Polygon(hdc, czh, 6);
					Polygon(hdc, dzh, 5);
					Polygon(hdc, ezh, 6);
					Polygon(hdc, fzh, 6);
				break;
				}
			}
			
			switch(uh){
				case 1: {
					Polygon(hdc, buh, 6);
					Polygon(hdc, cuh, 6);
					break;
				}
				case 2: {
					Polygon(hdc, auh, 5);
					Polygon(hdc, buh, 6);
					Polygon(hdc, guh, 7);
					Polygon(hdc, duh, 5);
					Polygon(hdc, euh, 6);
					break;
				}
				case 3:{
					Polygon(hdc, auh, 5);
					Polygon(hdc, buh, 6);
					Polygon(hdc, guh, 7);
					Polygon(hdc, cuh, 6);
					Polygon(hdc, duh, 5);
					break;
				}
				case 4:{
					Polygon(hdc, fuh, 6);
					Polygon(hdc, guh, 7);
					Polygon(hdc, buh, 6);
					Polygon(hdc, cuh, 6);
					break;
				}
				case 5:{
					Polygon(hdc, auh, 5);
					Polygon(hdc, fuh, 6);
					Polygon(hdc, guh, 7);
					Polygon(hdc, cuh, 6);
					Polygon(hdc, duh, 5);
					break;
				}
				case 6:{
					Polygon(hdc, auh, 5);
					Polygon(hdc, fuh, 6);
					Polygon(hdc, guh, 7);
					Polygon(hdc, cuh, 6);
					Polygon(hdc, duh, 5);
					Polygon(hdc, euh, 6);
					break;
				}
				case 7:{
					Polygon(hdc, auh, 5);
					Polygon(hdc, buh, 6);
					Polygon(hdc, cuh, 6);
					break;
				}
				case 8:{
					Polygon(hdc, auh, 5);
					Polygon(hdc, buh, 6);
					Polygon(hdc, cuh, 6);
					Polygon(hdc, duh, 5);
					Polygon(hdc, euh, 6);
					Polygon(hdc, fuh, 6);
					Polygon(hdc, guh, 7);
					break;
				}
				case 9:{
					Polygon(hdc, auh, 5);
					Polygon(hdc, buh, 6);
					Polygon(hdc, cuh, 6);
					Polygon(hdc, duh, 5);
					Polygon(hdc, fuh, 6);
					Polygon(hdc, guh, 7);
					break;
				}
				case 0:{
					Polygon(hdc, auh, 5);
					Polygon(hdc, buh, 6);
					Polygon(hdc, cuh, 6);
					Polygon(hdc, duh, 5);
					Polygon(hdc, euh, 6);
					Polygon(hdc, fuh, 6);
				break;
				}
			}
			
			switch(zmin)
			{
				case 1: {
					Polygon(hdc, bzm, 6);
					Polygon(hdc, czm, 6);
					break;
				}
				case 2: {
					Polygon(hdc, azm, 5);
					Polygon(hdc, bzm, 6);
					Polygon(hdc, gzm, 7);
					Polygon(hdc, dzm, 5);
					Polygon(hdc, ezm, 6);
					break;
				}
				case 3:{
					Polygon(hdc, azm, 5);
					Polygon(hdc, bzm, 6);
					Polygon(hdc, gzm, 7);
					Polygon(hdc, czm, 6);
					Polygon(hdc, dzm, 5);
					break;
				}
				case 4:{
					Polygon(hdc, fzm, 6);
					Polygon(hdc, gzm, 7);
					Polygon(hdc, bzm, 6);
					Polygon(hdc, czm, 6);
					break;
				}
				case 5:{
					Polygon(hdc, azm, 5);
					Polygon(hdc, fzm, 6);
					Polygon(hdc, gzm, 7);
					Polygon(hdc, czm, 6);
					Polygon(hdc, dzm, 5);
					break;
				}
				case 0:{
					Polygon(hdc, azm, 5);
					Polygon(hdc, bzm, 6);
					Polygon(hdc, czm, 6);
					Polygon(hdc, dzm, 5);
					Polygon(hdc, ezm, 6);
					Polygon(hdc, fzm, 6);
				break;
				}
			}
			
			switch(umin){
				case 1: {
					Polygon(hdc, bum, 6);
					Polygon(hdc, cum, 6);
					break;
				}
				case 2: {
					Polygon(hdc, aum, 5);
					Polygon(hdc, bum, 6);
					Polygon(hdc, gum, 7);
					Polygon(hdc, dum, 5);
					Polygon(hdc, eum, 6);
					break;
				}
				case 3:{
					Polygon(hdc, aum, 5);
					Polygon(hdc, bum, 6);
					Polygon(hdc, gum, 7);
					Polygon(hdc, cum, 6);
					Polygon(hdc, dum, 5);
					break;
				}
				case 4:{
					Polygon(hdc, fum, 6);
					Polygon(hdc, gum, 7);
					Polygon(hdc, bum, 6);
					Polygon(hdc, cum, 6);
					break;
				}
				case 5:{
					Polygon(hdc, aum, 5);
					Polygon(hdc, fum, 6);
					Polygon(hdc, gum, 7);
					Polygon(hdc, cum, 6);
					Polygon(hdc, dum, 5);
					break;
				}
				case 6:{
					Polygon(hdc, aum, 5);
					Polygon(hdc, fum, 6);
					Polygon(hdc, gum, 7);
					Polygon(hdc, cum, 6);
					Polygon(hdc, dum, 5);
					Polygon(hdc, eum, 6);
					break;
				}
				case 7:{
					Polygon(hdc, aum, 5);
					Polygon(hdc, bum, 6);
					Polygon(hdc, cum, 6);
					break;
				}
				case 8:{
					Polygon(hdc, aum, 5);
					Polygon(hdc, bum, 6);
					Polygon(hdc, cum, 6);
					Polygon(hdc, dum, 5);
					Polygon(hdc, eum, 6);
					Polygon(hdc, fum, 6);
					Polygon(hdc, gum, 7);
					break;
				}
				case 9:{
					Polygon(hdc, aum, 5);
					Polygon(hdc, bum, 6);
					Polygon(hdc, cum, 6);
					Polygon(hdc, dum, 5);
					Polygon(hdc, fum, 6);
					Polygon(hdc, gum, 7);
					break;
				}
				case 0:{
					Polygon(hdc, aum, 5);
					Polygon(hdc, bum, 6);
					Polygon(hdc, cum, 6);
					Polygon(hdc, dum, 5);
					Polygon(hdc, eum, 6);
					Polygon(hdc, fum, 6);
				break;
				}
			}
			switch(zsec){
				case 1: {
					Polygon(hdc, bzs, 6);
					Polygon(hdc, czs, 6);
					break;
				}
				case 2: {
					Polygon(hdc, azs, 5);
					Polygon(hdc, bzs, 6);
					Polygon(hdc, gzs, 7);
					Polygon(hdc, dzs, 5);
					Polygon(hdc, ezs, 6);
					break;
				}
				case 3:{
					Polygon(hdc, azs, 5);
					Polygon(hdc, bzs, 6);
					Polygon(hdc, gzs, 7);
					Polygon(hdc, czs, 6);
					Polygon(hdc, dzs, 5);
					break;
				}
				case 4:{
					Polygon(hdc, fzs, 6);
					Polygon(hdc, gzs, 7);
					Polygon(hdc, bzs, 6);
					Polygon(hdc, czs, 6);
					break;
				}
				case 5:{
					Polygon(hdc, azs, 5);
					Polygon(hdc, fzs, 6);
					Polygon(hdc, gzs, 7);
					Polygon(hdc, czs, 6);
					Polygon(hdc, dzs, 5);
					break;
				}
				case 0:{
					Polygon(hdc, azs, 5);
					Polygon(hdc, bzs, 6);
					Polygon(hdc, czs, 6);
					Polygon(hdc, dzs, 5);
					Polygon(hdc, ezs, 6);
					Polygon(hdc, fzs, 6);
				break;
				}
			}
			
			switch(usec){
				case 1: {
					Polygon(hdc, bus, 6);
					Polygon(hdc, cus, 6);
					break;
				}
				case 2: {
					Polygon(hdc, aus, 5);
					Polygon(hdc, bus, 6);
					Polygon(hdc, gus, 7);
					Polygon(hdc, dus, 5);
					Polygon(hdc, eus, 6);
					break;
				}
				case 3:{
					Polygon(hdc, aus, 5);
					Polygon(hdc, bus, 6);
					Polygon(hdc, gus, 7);
					Polygon(hdc, cus, 6);
					Polygon(hdc, dus, 5);
					break;
				}
				case 4:{
					Polygon(hdc, fus, 6);
					Polygon(hdc, gus, 7);
					Polygon(hdc, bus, 6);
					Polygon(hdc, cus, 6);
					break;
				}
				case 5:{
					Polygon(hdc, aus, 5);
					Polygon(hdc, fus, 6);
					Polygon(hdc, gus, 7);
					Polygon(hdc, cus, 6);
					Polygon(hdc, dus, 5);
					break;
				}
				case 6:{
					Polygon(hdc, aus, 5);
					Polygon(hdc, fus, 6);
					Polygon(hdc, gus, 7);
					Polygon(hdc, cus, 6);
					Polygon(hdc, dus, 5);
					Polygon(hdc, eus, 6);
					break;
				}
				case 7:{
					Polygon(hdc, aus, 5);
					Polygon(hdc, bus, 6);
					Polygon(hdc, cus, 6);
					break;
				}
				case 8:{
					Polygon(hdc, aus, 5);
					Polygon(hdc, bus, 6);
					Polygon(hdc, cus, 6);
					Polygon(hdc, dus, 5);
					Polygon(hdc, eus, 6);
					Polygon(hdc, fus, 6);
					Polygon(hdc, gus, 7);
					break;
				}
				case 9:{
					Polygon(hdc, aus, 5);
					Polygon(hdc, bus, 6);
					Polygon(hdc, cus, 6);
					Polygon(hdc, dus, 5);
					Polygon(hdc, fus, 6);
					Polygon(hdc, gus, 7);
					break;
				}
				case 0:{
					Polygon(hdc, aus, 5);
					Polygon(hdc, bus, 6);
					Polygon(hdc, cus, 6);
					Polygon(hdc, dus, 5);
					Polygon(hdc, eus, 6);
					Polygon(hdc, fus, 6);
				break;
				}
			}
			
			if(i%2 == 0){
				SelectObject(hdc, white);
				SelectObject(hdc, brwhite);
				Ellipse(hdc, 440-10, 220-10+40,440+10, 220+10+40);//405
				Ellipse(hdc, 440-10, 260-10+40,440+10, 260+10+40);
				Ellipse(hdc, 770-10, 220-10+40,770+10, 220+10+40);
				Ellipse(hdc, 770-10, 260-10+40,770+10, 260+10+40);			
			}
			else{
				SelectObject(hdc, penred);
				SelectObject(hdc, red);
				Ellipse(hdc, 440-10, 220-10+40,440+10, 220+10+40);
				Ellipse(hdc, 440-10, 260-10+40,440+10, 260+10+40);
				Ellipse(hdc, 770-10, 220-10+40,770+10, 220+10+40);
				Ellipse(hdc, 770-10, 260-10+40,770+10, 260+10+40);			
			}	
			
			EndPaint(hwnd, &ps);
			return 0;
		}

		case WM_TIMER:
		{	
			i++;
			InvalidateRect(hwnd, NULL, FALSE);	
			break;
		}
		
		case WM_DESTROY:
		PostQuitMessage (0);
		return 0;
	}
	
	return DefWindowProc(hwnd, iMsg,wParam, lParam) ;
}
