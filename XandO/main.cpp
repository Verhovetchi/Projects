#include <windows.h>
#define DIVISIONS 3
#define MoveTo(hdc, x, y) MoveToEx(hdc, x, y, NULL)
#include <iostream>

using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void winer(int n)
{
	switch(n){
		
		case 1:{
			MessageBox(
				NULL,
				"Win X",
                TEXT("Sfarsit!!!"),
                MB_ICONEXCLAMATION
			);
		}break;
		
		case 2:{
			MessageBox(
                NULL,
                "Win O",
                TEXT("Sfarsit!!!"),
                MB_ICONEXCLAMATION
			);	
		}break;
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,PSTR szCmdLine, int iCmdShow)
{
	static char szAppName[] = "Games XandO";
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
	hwnd = CreateWindow(
		szAppName, "X and O",
		WS_OVERLAPPEDWINDOW,				
		CW_USEDEFAULT, 
		CW_USEDEFAULT,
		400, 
		400,
		NULL, 
		NULL, 
		hInstance, 
		NULL
	);
	
	ShowWindow(hwnd, iCmdShow);
	
	UpdateWindow(hwnd);
	
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static BOOL fState[DIVISIONS][DIVISIONS];
	static int cxBlock, cyBlock, cxClient, cyClient, i = 0, res[3][3] = {};
	int x, y;
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;
	HPEN pen = CreatePen(PS_SOLID, 4, RGB(0, 0, 0));
	HPEN circle = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
	HPEN ics = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
	HPEN win = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	HBRUSH fon = CreateSolidBrush(RGB(222, 212, 240));
	
	switch(iMsg)
	{
		case WM_SIZE :{
			cxClient = LOWORD (lParam);
			cyClient = HIWORD (lParam);
			cxBlock = 100;
			cyBlock = 100;
			
			return 0;
		}
	
		case WM_GETMINMAXINFO:{
            LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
            lpMMI->ptMinTrackSize.x = 400;
            lpMMI->ptMinTrackSize.y = 400;
            lpMMI->ptMaxTrackSize.x = 400;
            lpMMI->ptMaxTrackSize.y = 400;
        }
        break;
	
		case WM_LBUTTONDOWN :{
			x = (LOWORD(lParam) - 41) / cxBlock;
			y = (HIWORD(lParam) - 30) / cyBlock;
			
			i++;
//			cout << "x = " << x << "  y = " << y << endl;
			if(x < DIVISIONS && y < DIVISIONS){	
				fState [x][y] ^= 1;
				rect.left = cxClient / 2 - 150;
				rect.top = cyClient / 2 - 150;
				rect.right = cyClient / 2 + 160;
				rect.bottom = cyClient / 2 + 160;
				InvalidateRect(hwnd, &rect, FALSE);
				
				if(i % 2 != 0)
					res[y][x] = 1;
				else
					res[y][x] = 2;
			}
			else
				MessageBeep(0);
			
			return 0;
		}
	
		case WM_PAINT :{
			
			hdc = BeginPaint(hwnd, &ps);
			if(i ==0 ){
				SelectObject(hdc, fon);
				Rectangle(hdc, 0, 0, cxClient, cyClient);
			}
			
			for(x = 0; x < DIVISIONS; x++){
				for(y = 0; y < DIVISIONS; y++){
					SelectObject(hdc, pen);
					
					for(int i = -50; i <= 50 ; i += 100){
						MoveToEx(hdc, cxClient / 2 + i, cyClient / 2 - 150, NULL);
						LineTo(hdc, cxClient / 2 + i, cyClient / 2 + 150);
					}
					
					for(int i = -50; i <= 50 ; i += 100){
						MoveToEx(hdc, cxClient / 2 - 150, cyClient / 2 + i, NULL);
						LineTo(hdc, cxClient / 2 + 150, cyClient / 2 + i);
					}
								
					if(fState[x][y]){
						if(i <= 9){
							fState[x][y] = false;
							
							if(i % 2 != 0){
								SelectObject(hdc, ics);
								MoveTo(hdc, x * cxBlock + 61, y * cyBlock + 50);
								LineTo(hdc, (x + 1) * cxBlock + 21, (y + 1) * cyBlock + 10);
								MoveTo(hdc, x * cxBlock + 61, (y + 1) * cyBlock + 10);
								LineTo(hdc,(x + 1) * cxBlock + 21, y * cyBlock + 50);
							}
							else{
								SelectObject(hdc, circle);
								SelectObject(hdc, fon);
								Ellipse(hdc, x * cxBlock + 61,y * cyBlock + 50, (x + 1) * cxBlock + 21,(y + 1) * cyBlock + 10);
							}
							
							if((res[0][0] == 1 && res[1][1] == 1 && res[2][2] == 1) ||
								(res[0][0] == 2 && res[1][1] == 2 && res[2][2] == 2)){
								
								SelectObject(hdc, win);
								MoveToEx(hdc, cxClient / 2 - 150, cyClient / 2 - 150, NULL);
								LineTo(hdc, cxClient / 2 + 150, cyClient / 2 + 150);
								
								if(res[0][0] == 1){
									winer(1); 
									goto fin;
								}
									
								else{
									winer(2);
									goto fin;
								}
							}
							
							if((res[0][2] == 1 && res[1][1] == 1 && res[2][0] == 1) ||
								(res[0][2] == 2 && res[1][1] == 2 && res[2][0] == 2)){
								
								SelectObject(hdc, win);
								MoveToEx(hdc, cxClient / 2 + 150, cyClient / 2 - 150, NULL);
								LineTo(hdc, cxClient / 2 - 150, cyClient / 2 + 150);
								
								if(res[0][2] == 1){
									winer(1); 
									goto fin;
								}
									
								else{
									winer(2);
									goto fin;
								}
							}
							
							if((res[0][0] == 1 && res[1][0] == 1 && res[2][0] == 1) ||
								(res[0][0] == 2 && res[1][0] == 2 && res[2][0] == 2)){
								
								SelectObject(hdc, win);
								MoveToEx(hdc, cxClient/2-100, cyClient/2 - 150, NULL);
								LineTo(hdc, cxClient/2 - 100, cyClient/2 + 150);
								if(res[0][0] == 1){
									winer(1); 
									goto fin;
								}
									
								else{
									winer(2);
									goto fin;
								}
							}
							
							if((res[0][1] == 1 && res[1][1] == 1 && res[2][1] == 1) ||
								(res[0][1] == 2 && res[1][1] == 2 && res[2][1] == 2)){
								
								SelectObject(hdc, win);
								MoveToEx(hdc, cxClient / 2, cyClient / 2 - 150, NULL);
								LineTo(hdc, cxClient / 2, cyClient / 2 + 150);
								
								if(res[0][1] == 1){
									winer(1); 
									goto fin;
								}
									
								else{
									winer(2);
									goto fin;
								}
							}
							
							if((res[0][2] == 1 && res[1][2] == 1 && res[2][2] == 1) ||
								(res[0][2] == 2 && res[1][2] == 2 && res[2][2] == 2)){
								
								SelectObject(hdc, win);
								MoveToEx(hdc, cxClient / 2 + 100, cyClient / 2 - 150, NULL);
								LineTo(hdc, cxClient / 2 + 100, cyClient / 2 + 150);
								
								if(res[0][2] == 1){
									winer(1); 
									goto fin;
								}
									
								else{
									winer(2);
									goto fin;
								}
							}
							
							if((res[0][0] == 1 && res[0][1] == 1 && res[0][2] == 1) ||
								(res[0][0] == 2 && res[0][1] == 2 && res[0][2] == 2)){
								
								SelectObject(hdc, win);
								MoveToEx(hdc, cxClient / 2 - 150, cyClient / 2 - 100, NULL);
								LineTo(hdc, cxClient / 2 + 150, cyClient / 2 - 100);
								
								if(res[0][0] == 1){
									winer(1); 
									goto fin;
								}
									
								else{
									winer(2);
									goto fin;
								}
							}
							
							if((res[1][0] == 1 && res[1][1] == 1 && res[1][2] == 1) ||
								(res[1][0] == 2 && res[1][1] == 2 && res[1][2] == 2)){
								
								SelectObject(hdc, win);
								MoveToEx(hdc, cxClient / 2 - 150, cyClient / 2, NULL);
								LineTo(hdc, cxClient / 2 + 150, cyClient / 2);
								
								if(res[1][0] == 1){
									winer(1); 
									goto fin;
								}
									
								else{
									winer(2);
									goto fin;
								}
							}
							
							if((res[2][0] == 1 && res[2][1] == 1 && res[2][2] == 1) ||
								(res[2][0] == 2 && res[2][1] == 2 && res[2][2] == 2)){
								
								SelectObject(hdc, win);
								MoveToEx(hdc, cxClient / 2 - 150, cyClient / 2 + 100, NULL);
								LineTo(hdc, cxClient / 2 + 150, cyClient / 2 + 100);
								
								if(res[2][0] == 1){
									winer(1); 
									goto fin;
								}
									
								else{
									winer(2);
									goto fin;
								}
							}
							
							if(i == 9){
								MessageBox(
									NULL,
		                            "Egalitate",
		                            TEXT("Sfarsit!!!"),
		                            MB_ICONEXCLAMATION
						    	);
						    	
						    	goto fin;
							}
						}
					}		
				}
			}
			
			EndPaint(hwnd, &ps);
			
			return 0;
		}
		
		case WM_DESTROY :{
			fin:
			PostQuitMessage(0);
			return 0;
		}
	}
	
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
