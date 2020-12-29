#include <windows.h>
#define DIVISIONS 3
#define MoveTo(hdc, x, y) MoveToEx(hdc, x, y, NULL)
#include <iostream>
#include <math.h>

using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static char szAppName[] = "Checker1";
	HWND hwnd;
	MSG msg;
	WNDCLASSEX wndclass;
	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground =(HBRUSH) GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wndclass);
	hwnd = CreateWindow(szAppName, "Checker1 Mouse Hit-Test Demo",
	WS_OVERLAPPEDWINDOW,
	0, 0,
	1368, 728,
	NULL, NULL, hInstance, NULL);
	
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	SetTimer(hwnd, 0, 35, NULL);
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static int option = 1;
	RECT rect;
	static int cxClient, cyClient, x = 0, y = 0, i = 0;
	static float angle1 = M_PI/4, angle2 = -M_PI/4, angle3 = M_PI/4, angle4 = M_PI/4, sigma = 0;
	
	HPEN packman = CreatePen(PS_SOLID, 3, RGB(255, 255, 1));
	HBRUSH intpackman = CreateSolidBrush(RGB(255, 255, 1));
	
	switch(iMsg)
	{
		case WM_SIZE :{
			cxClient = LOWORD (lParam);
			cyClient = HIWORD (lParam);
			return 0;
		}
			
		case WM_PAINT :{
			InvalidateRect(hwnd, NULL, TRUE);
			hdc = BeginPaint(hwnd, &ps);			
			
			SelectObject(hdc, packman);
			SelectObject(hdc, intpackman);
			
			Pie(hdc, cxClient / 2 - 30 + x, cyClient / 2 - 30 + y, cxClient / 2 + 30 + x, cyClient / 2 + 30 + y, 
			cxClient / 2 + 30 * sin(angle1) + x, cyClient / 2 + 30 * sin(angle2) + y,
			cxClient / 2 + 30 * sin(angle3) + x, cyClient / 2 + 30 * sin(angle4) + y); 
			
			EndPaint(hwnd, &ps);
			return 0;
		}
		
		case WM_KEYDOWN:{
	        
			switch(wParam){
	        	
				case VK_RIGHT:{
	                option = 1;
		            break;
		        }
		        
				case VK_LEFT:{	
					option = 2;	
		            break;
		        }
		    
		        case VK_UP:{
		        	option = 3;
					break;
				}
				
				case VK_DOWN:{
		        	option = 4;
					break;
				}
	        }
	
	        InvalidateRect(hwnd, NULL, TRUE);
	        break;
	    }
	    
	    case WM_TIMER:{
			
			if(option == 1){
				angle1 = M_PI / 4 + sigma;
		        	angle2 = 7 * M_PI / 4 + sigma;
		        	angle3 = M_PI / 4 + sigma;
		        	angle4 = M_PI / 4 - sigma;
		       		
		       		if(i % 8 < 4)
		       			sigma += M_PI / 17;
					else
						sigma -= M_PI / 17;
				
		       		i++;
		       		x+=10;
			}
				
			else if(option == 2){
				angle1 = -M_PI / 4 - sigma;
		        	angle2 = M_PI / 4 - sigma;
		        	angle3 = -M_PI / 4 - sigma;
		        	angle4 = -M_PI / 4 + sigma;
		        	
					if(i % 8 < 4)
		       			sigma += M_PI/17;
					else
						sigma -= M_PI/17;
					
		       		i++;
					x-=10;
			}
				
			else if(option == 3){
				angle1 = -3 * M_PI / 4 - sigma; 
					angle2 = -3 * M_PI / 4 + sigma; 
					angle3 = 3 * M_PI / 4 + sigma;
					angle4 = -3 * M_PI / 4 + sigma;
					
					if(i % 8 < 4)
		       			sigma += M_PI / 17;
					else
						sigma -= M_PI / 17;
					
		       		i++;
		       		y-=10;
			}
				
			else{
				angle1 = 3 * M_PI / 4 + sigma;
		        	angle2 = 3 * M_PI / 4 - sigma;
		        	angle3 = -3 * M_PI / 4 - sigma;
		        	angle4 = 3 * M_PI / 4 - sigma;
		        	
		        	if(i % 8 < 4)
		       			sigma += M_PI / 17;
					else
						sigma -= M_PI / 17;
					
		       		i++;
				y+=10;
			} 
				
				
			InvalidateRect(hwnd, NULL, FALSE);	
			break;
		}
				
		return 0;
		
		case WM_DESTROY :{
			PostQuitMessage(0);
			return 0;	
		}
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
