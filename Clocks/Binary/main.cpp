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
	WNDCLASSEX  wndclass ;
	
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
	              CW_USEDEFAULT, CW_USEDEFAULT,
	              CW_USEDEFAULT, CW_USEDEFAULT,
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
	HDC         hdc;
	PAINTSTRUCT ps;
	
	SYSTEMTIME lt;
    GetLocalTime(&lt);
    
    int zsec = lt.wSecond / 10, usec = lt.wSecond % 10;
    int zmin = lt.wMinute / 10, umin = lt.wMinute % 10;
	int zh = lt.wHour / 10, uh = lt.wHour % 10;
    int row, col;
    
	HPEN pen = CreatePen(PS_SOLID, 4, RGB(0, 0, 0));
	
	HBRUSH aqua = CreateSolidBrush(RGB(56, 239, 235));
	HBRUSH clasic = CreateSolidBrush(RGB(172, 172, 172));
	HBRUSH fon = CreateSolidBrush(RGB(240, 240, 240));

	HBRUSH secunde = CreateSolidBrush(RGB(0, 0, 255));
	HBRUSH minute = CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH ore = CreateSolidBrush(RGB(255, 0, 0));
	
	switch (iMsg)
	{
		case WM_SIZE:
		{
			cxClient = LOWORD (lParam);
			cyClient = HIWORD (lParam);
			return 0;
		}
		
//		case WM_GETMINMAXINFO:{
//            LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
//            lpMMI->ptMinTrackSize.x = 940;
//            lpMMI->ptMinTrackSize.y = 445;
//            lpMMI->ptMaxTrackSize.x = 1000;
//            lpMMI->ptMaxTrackSize.y = 900;
//        }
//        break;
	
		case WM_PAINT:
		{
			hdc = BeginPaint(hwnd, &ps);
			
			SelectObject(hdc, fon);
			Rectangle(hdc, 0, 0, cxClient, cyClient);	
			SelectObject(hdc, pen);
			SelectObject(hdc, aqua);

			MoveToEx(hdc, cxClient/2, cyClient/2, NULL);
		
			Rectangle(hdc, cxClient/2 - 150, cyClient/2 - 200, cxClient/2 + 150, cyClient/2 + 200); // mijloc
			
			for(int j = -200; j < 200; j += 100){
				for(int i = -150; i <= 0; i += 150){
					Rectangle(hdc, cxClient/2 + i, cyClient/2 + j, cxClient/2 + i + 150, cyClient/2 + j + 100);	
				}		
			} 
				
			Rectangle(hdc, cxClient/2 + 160, cyClient/2 - 200, cxClient/2 + 460, cyClient/2 + 200); // dreapta
			
			for(int j = -200; j < 200; j += 100){
				for(int i = -150; i <= 0; i += 150){
					Rectangle(hdc, cxClient/2 + i + 310, cyClient/2 + j, cxClient/2 + i + 460, cyClient/2 + j + 100);
				}
			}   
				
			Rectangle(hdc, cxClient/2 - 160, cyClient/2 - 200, cxClient/2 - 460, cyClient/2 + 200); // stanga
			
			for(int j = -200; j < 200; j += 100){
				for(int i = -150; i <= 0; i += 150){
					Rectangle(hdc, cxClient/2 + i - 310, cyClient/2 + j, cxClient/2 + i - 160, cyClient/2 + j + 100);
				}
			}

			if(zsec / 4 == 1)
			{
				row = -100;
				col = -150;
				SelectObject(hdc, secunde);
				Rectangle(hdc, cxClient/2 + col + 310, cyClient/2 + row, cxClient/2 + col + 460, cyClient/2 + row + 100);
				SelectObject(hdc, clasic);
				zsec = zsec % 4;
			}
			
			if(zsec / 2 == 1)	
			{
				row = 0;
				col = -150;
				SelectObject(hdc, secunde);
				Rectangle(hdc, cxClient/2 + col + 310, cyClient/2 + row, cxClient/2 + col + 460, cyClient/2 + row + 100);
				SelectObject(hdc, clasic);
				zsec = zsec % 2;
			}
			
			if(zsec == 1)
			{
				row = 100;
				col = -150;
				SelectObject(hdc, secunde);
				Rectangle(hdc, cxClient/2 + col + 310, cyClient/2 + row, cxClient/2 + col + 460, cyClient/2 + row + 100);
				SelectObject(hdc, clasic);
			}
			
			if(usec / 8 == 1)
			{
				row = -200;
				col = 0;
				SelectObject(hdc, secunde);
				Rectangle(hdc, cxClient/2 + col + 310, cyClient/2 + row, cxClient/2 + col + 460, cyClient/2 + row + 100);
				SelectObject(hdc, clasic);
				usec = usec % 8;
			}
			
			if(usec / 4 == 1)
			{
				row = -100;
				col = 0;
				SelectObject(hdc, secunde);
				Rectangle(hdc, cxClient/2 + col + 310, cyClient/2 + row, cxClient/2 + col + 460, cyClient/2 + row + 100);
				SelectObject(hdc, clasic);
				usec = usec % 4;
			}
			if(usec / 2 == 1)	
			{
				row = 0;
				col = 0;
				SelectObject(hdc, secunde);
				Rectangle(hdc, cxClient/2 + col + 310, cyClient/2 + row, cxClient/2 + col + 460, cyClient/2 + row + 100);
				SelectObject(hdc, clasic);
				usec = usec % 2;
			}
			if(usec == 1)
			{
				row = 100;
				col = 0;
				SelectObject(hdc, secunde);
				Rectangle(hdc, cxClient/2 + col + 310, cyClient/2 + row, cxClient/2 + col + 460, cyClient/2 + row + 100);
				SelectObject(hdc, clasic);
			}
	
			if(zmin / 4 == 1)
			{
				row = -100;
				col = -150;
				SelectObject(hdc, minute);
				Rectangle(hdc, cxClient/2 + col, cyClient/2 + row, cxClient/2 + col + 150, cyClient/2 + row + 100);
				SelectObject(hdc, clasic);
				zmin = zmin % 4;
			}
			
			if(zmin / 2 == 1)	
			{
				row = 0;
				col = -150;
				SelectObject(hdc, minute);
				Rectangle(hdc, cxClient/2 + col, cyClient/2 + row, cxClient/2 + col + 150, cyClient/2 + row + 100);
				SelectObject(hdc, clasic);
				zmin = zmin % 2;
			}
			
			if(zmin == 1)
			{
				row = 100;
				col = -150;
				SelectObject(hdc, minute);
				Rectangle(hdc, cxClient/2 + col, cyClient/2 + row, cxClient/2 + col + 150, cyClient/2 + row + 100);
				SelectObject(hdc, clasic);
			}
			
			if(umin / 8 == 1)
			{
				row = -200;
				col = 0;
				SelectObject(hdc, minute);
				Rectangle(hdc, cxClient/2 + col, cyClient/2 + row, cxClient/2 + col + 150, cyClient/2 + row + 100);
				SelectObject(hdc, clasic);
				umin = umin % 8;
			}
			
			if(umin / 4 == 1)
			{
				row = -100;
				col = 0;
				SelectObject(hdc, minute);
				Rectangle(hdc, cxClient/2 + col, cyClient/2 + row, cxClient/2 + col + 150, cyClient/2 + row + 100);
				SelectObject(hdc, clasic);
				umin = umin % 4;
			}
			
			if(umin / 2 == 1)	
			{
				row = 0;
				col = 0;
				SelectObject(hdc, minute);
				Rectangle(hdc, cxClient/2 + col, cyClient/2 + row, cxClient/2 + col + 150, cyClient/2 + row + 100);
				SelectObject(hdc, clasic);
				umin = umin % 2;
			}
			
			if(umin == 1)
			{
				row = 100;
				col = 0;
				SelectObject(hdc, minute);
				Rectangle(hdc, cxClient/2 + col, cyClient/2 + row, cxClient/2 + col + 150, cyClient/2 + row + 100);
				SelectObject(hdc, clasic);
			}
			
			if(zh / 2 == 1)	
			{
				row = 0;
				col = -150;
				SelectObject(hdc, ore);
				Rectangle(hdc, cxClient/2 + col - 310, cyClient/2 + row, cxClient/2 + col - 160, cyClient/2 + row + 100);
				SelectObject(hdc, clasic);
				zh = zh % 2;
			}
			if(zh == 1)
			{
				row = 100;
				col = -150;
				SelectObject(hdc, ore);
				Rectangle(hdc, cxClient/2 + col - 310, cyClient/2 + row, cxClient/2 + col - 160, cyClient/2 + row + 100);
				SelectObject(hdc, clasic);
			}
			
			if(uh / 8 == 1)
			{
				row = -200;
				col = 0;
				SelectObject(hdc, ore);
				Rectangle(hdc, cxClient/2 + col - 310, cyClient/2 + row, cxClient/2 + col - 160, cyClient/2 + row + 100);
				SelectObject(hdc, clasic);
				uh = uh % 8;
			}
			
			if(uh / 4 == 1)
			{
				row = -100;
				col = 0;
				SelectObject(hdc, ore);
				Rectangle(hdc, cxClient/2 + col - 310, cyClient/2 + row, cxClient/2 + col - 160, cyClient/2 + row + 100);
				SelectObject(hdc, clasic);
				uh = uh % 4;
			}
			
			if(uh / 2 == 1)	
			{
				row = 0;
				col = 0;
				SelectObject(hdc, ore);
				Rectangle(hdc, cxClient/2 + col - 310, cyClient/2 + row, cxClient/2 + col - 160, cyClient/2 + row + 100);
				SelectObject(hdc, clasic);
				uh = uh % 2;
			}
			
			if(uh == 1)
			{
				row = 100;
				col = 0;
				SelectObject(hdc, ore);
				Rectangle(hdc, cxClient/2 + col - 310, cyClient/2 + row, cxClient/2 + col - 160, cyClient/2 + row + 100);
				SelectObject(hdc, clasic);
			}
		
			EndPaint(hwnd, &ps);
			return 0;
		}

		case WM_TIMER:
		{						
			InvalidateRect(hwnd, NULL, FALSE);	
			break;
		}
		
		case WM_DESTROY:
		PostQuitMessage (0);
		return 0;
	}
	
	return DefWindowProc(hwnd, iMsg,wParam, lParam) ;
}
