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
     
     //
     SYSTEMTIME lt = {0};
  
    GetLocalTime(&lt);
  
    wprintf(L"The local time is: %d:%d:%d\n", 
        lt.wHour, lt.wMinute, lt.wSecond);
     //
     
	 wndclass.cbSize        = sizeof (wndclass) ;
     wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
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
	HDC         hdc ;
	static int  i = 0;
	int cof = 225;
	PAINTSTRUCT ps ;
	float alpha = 0;
	SYSTEMTIME lt;
    GetLocalTime(&lt);
	static float sec = lt.wSecond*(M_PI/30);
	static float min = lt.wMinute*(M_PI/30);
	static float hour = lt.wHour*(M_PI/6) + lt.wMinute/12*(M_PI/30);
	
	HBRUSH center = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH blt = CreateSolidBrush(RGB(198,252,221));
	HBRUSH body = CreateSolidBrush(RGB(27,30,156));
	
	switch (iMsg)
	{
		case WM_SIZE:
		cxClient = LOWORD (lParam) ;
		cyClient = HIWORD (lParam) ;
		return 0 ;
	
		case WM_PAINT:
			hdc = BeginPaint(hwnd, &ps);
			
			SelectObject(hdc, body);
			Ellipse(hdc, (cxClient/2)-235, (cyClient/2)-235, (cxClient/2)+235, (cyClient/2)+235);
			SelectObject(hdc, blt);
			Ellipse(hdc, (cxClient/2)-cof, (cyClient/2)-cof, (cxClient/2)+cof, (cyClient/2)+cof);
			SelectObject(hdc, center);
			Ellipse(hdc, (cxClient/2)-10, (cyClient/2)-10, (cxClient/2)+10, (cyClient/2)+10);
			
			for(float alpha = 0; alpha < 2*M_PI; alpha += M_PI/6)
			{
				MoveToEx(hdc, cxClient/2 + sin(alpha) * cof, cyClient/2 + cos(alpha)*cof, NULL);
				LineTo(hdc, cxClient/2 + sin(alpha) * 200, cyClient/2 + cos(alpha)*200);
			}
			
			for(float alpha = 0; alpha < 2*M_PI; alpha += M_PI/30)
			{
				MoveToEx(hdc, cxClient/2 + sin(alpha) * cof, cyClient/2 + cos(alpha)*cof, NULL);
				LineTo(hdc, cxClient/2 + sin(alpha) * 215, cyClient/2 + cos(alpha)*215);
			}
			
			SetBkColor(hdc, RGB(198,252,221));
			
			TextOut(hdc, cxClient/2 - 9 + sin(alpha) * 185, cyClient/2-10 - cos(alpha)*185, "XII", 3);
			alpha += M_PI/6;
			TextOut(hdc, cxClient/2 - 4 + sin(alpha) * 185, cyClient/2-10 - cos(alpha)*185, "I", 1);
			alpha += M_PI/6;
			TextOut(hdc, cxClient/2 - 4 + sin(alpha) * 185, cyClient/2-10 - cos(alpha)*185, "II", 2);
			alpha += M_PI/6;
			TextOut(hdc, cxClient/2 - 4 + sin(alpha) * 185, cyClient/2-8 - cos(alpha)*185, "III", 3);
			alpha += M_PI/6;
			TextOut(hdc, cxClient/2 - 4 + sin(alpha) * 185, cyClient/2-10 - cos(alpha)*185, "IV", 2);
			alpha += M_PI/6;
			TextOut(hdc, cxClient/2 - 4 + sin(alpha) * 185, cyClient/2-10 - cos(alpha)*185, "V", 1);
			alpha += M_PI/6;
			TextOut(hdc, cxClient/2 - 8 + sin(alpha) * 185, cyClient/2-10 - cos(alpha)*185, "VI", 2);
			alpha += M_PI/6;
			TextOut(hdc, cxClient/2 - 4 + sin(alpha) * 185, cyClient/2-10 - cos(alpha)*185, "VII", 3);
			alpha += M_PI/6;
			TextOut(hdc, cxClient/2 - 4 + sin(alpha) * 185, cyClient/2-10 - cos(alpha)*185, "VIII", 4);
			alpha += M_PI/6;
			TextOut(hdc, cxClient/2 - 4 + sin(alpha) * 185, cyClient/2-8 - cos(alpha)*185, "IX", 2);
			alpha += M_PI/6;
			TextOut(hdc, cxClient/2 - 4 + sin(alpha) * 185, cyClient/2-10 - cos(alpha)*185, "X", 1);
			alpha += M_PI/6;
			TextOut(hdc, cxClient/2 - 4 + sin(alpha) * 185, cyClient/2-10 - cos(alpha)*185, "XI", 2);
			
			SetTextColor(hdc, RGB(110,75,14));
			TextOut(hdc, cxClient/2 - 20, cyClient/2 + 60, "Rolex", 5);
			
			
			
			MoveToEx(hdc, cxClient/2, cyClient/2, NULL);
			LineTo(hdc, cxClient/2 + sin(sec) * 180, cyClient/2 - cos(sec)*180);
			
			MoveToEx(hdc, cxClient/2, cyClient/2, NULL);
			LineTo(hdc, cxClient/2 + sin(min) * 140, cyClient/2 - cos(min)*140);
			
			MoveToEx(hdc, cxClient/2, cyClient/2, NULL);
			LineTo(hdc, cxClient/2 + sin(hour) * 100, cyClient/2 - cos(hour)*100);
    		
			EndPaint(hwnd, &ps);
			
			
		return 0 ;
		
		case WM_TIMER:{
			
			sec = sec + M_PI/30;
			if(lt.wSecond == 0)
				min = min + M_PI/30;
			
			if(lt.wMinute%12==0 && lt.wSecond == 0)
				hour = hour + M_PI/30;	
			
			InvalidateRect(hwnd, NULL, FALSE);	
			
			break;
		}
		
		case WM_DESTROY:
		PostQuitMessage (0) ;
		return 0 ;
	}
	
	return DefWindowProc(hwnd, iMsg,wParam, lParam) ;
}
