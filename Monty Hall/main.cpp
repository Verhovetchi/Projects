#include <windows.h>
#include <iostream>
#include <conio.h>
#include <ctime>

HWND hwnd;
HDC hdc;

void Door(int nr, int cxClient, int cyClient, char *href)
{
	HANDLE hBitmap, hOldBitmap;
	HDC hCompatibleDC;
	BITMAP Bitmap;
	hBitmap = LoadImage(NULL, href, IMAGE_BITMAP, /*200*/200, /*200*/200, LR_LOADFROMFILE);
    GetObject(hBitmap, sizeof(BITMAP), &Bitmap);
    hCompatibleDC = CreateCompatibleDC(hdc);
    hOldBitmap = SelectObject(hCompatibleDC, hBitmap);
    GetClientRect(hwnd, NULL);
    StretchBlt(hdc,nr * cxClient / 5 + 2, cyClient / 2 - cyClient / 3 + 2, 197, 360, hCompatibleDC, 0, 0, Bitmap.bmWidth, 
       	 	   Bitmap.bmHeight, SRCCOPY);
    SelectObject(hCompatibleDC, hOldBitmap);
    DeleteObject(hBitmap);
    DeleteDC(hCompatibleDC);
}

using namespace std;

char character[3] = { 'm', 's', 's'};

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
PSTR szCmdLine, int iCmdShow)
{
	static char szAppName[] = "MoveChoise";
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
	hwnd = CreateWindow(szAppName, "Change your Choise",
	WS_OVERLAPPEDWINDOW,
	CW_USEDEFAULT, CW_USEDEFAULT,
	CW_USEDEFAULT, CW_USEDEFAULT,
	NULL, NULL, hInstance, NULL);
	
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
	PAINTSTRUCT ps;
	HPEN pen = CreatePen(PS_SOLID, 4, RGB(0, 0, 0));
	HBRUSH door = CreateSolidBrush(RGB(172, 172, 172));
	HBRUSH fon = CreateSolidBrush(RGB(59, 184, 24));
	HFONT hFont = CreateFont(30, 10, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
							 CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH, "Times New Roman");
	
	int first, second, third, these;
	static int i = 0, x, count = 0;
	static char prize[3];
	static int cxBlock, cyBlock, cxClient, cyClient;
	static int firstChoise, secondChoise;
	static int bonus;
	
	//
	switch(iMsg)
	{
		case WM_SIZE:{
			cxClient = LOWORD(lParam);
			cyClient = HIWORD(lParam);
		
			srand(time(NULL));
			
			these = rand() % 3;
			first = these;
			prize[i] = character[first];
			i++;
			
			repeat:
				these = rand()%3;
				second = these;
				if(second == first)
					goto repeat;
				else
					prize[i] = character[second];
				i++;
			
			repeat1:
				these = rand()%3;
				third = these;
				if(third == first || third == second)
					goto repeat1;
				else
					prize[i] = character[third];
					
//				for(int i = 0; i < 3; i++)
//					cout << prize[i] << " ";
				
				cout << endl;

			return 0;
		}
		//
		//
		case WM_LBUTTONDOWN :{
			cxBlock = 5 * LOWORD(lParam) / cxClient;
			cyBlock = HIWORD(lParam) / (cyClient + 1);
			ahead:
			count++;
			InvalidateRect(hwnd, NULL, FALSE);
			return 0;
		}
		//
		
		case WM_PAINT :{
			hdc = BeginPaint(hwnd, &ps);
			
//			for(int i = 0; i < 3; i++)
//				cout << prize[i] << "  ";
			
			cout << endl;
			
			x = cxBlock;
		
			if(count == 0){
			SelectObject(hdc, fon);
			SelectObject(hdc, hFont);
			Rectangle(hdc, 0, 0, cxClient, cyClient);
			SelectObject(hdc, pen);
			SelectObject(hdc, door);
			SetBkColor(hdc, RGB(30, 31, 44));
			SetTextColor(hdc, RGB(0, 0, 255));
			
			Door(1, cxClient, cyClient, "doorfin.bmp");
			TextOut(hdc, cxClient / 5 + cxClient / 10, cyClient / 2 - cyClient / 9, "1", 1);
			Door(2, cxClient, cyClient, "doorfin.bmp");
			TextOut(hdc, 2 * cxClient / 5 + cxClient / 10, cyClient / 2 - cyClient / 9, "2", 1);
			Door(3, cxClient, cyClient, "doorfin.bmp");
			
			TextOut(hdc, 3 * cxClient / 5 + cxClient / 10, cyClient / 2 - cyClient / 9, "3", 1);		
			}
			//Excelent
			else if(count == 1){
				SelectObject(hdc, hFont);
				firstChoise = x;
				cout << "First  choise : " << firstChoise << endl;
				
				SetBkColor(hdc, RGB(30, 31, 44));
						
				switch(firstChoise){
					case 1:{
						SetTextColor(hdc, RGB(255, 0, 0));
						TextOut(hdc, cxClient / 5 + cxClient / 25, cyClient / 2 - cyClient / 9, "Your choise", 11);
						SetTextColor(hdc, RGB(0, 0, 255));
						TextOut(hdc, 2 * cxClient / 5 + cxClient / 10, cyClient / 2 - cyClient / 9, "2", 1);
						TextOut(hdc, 3 * cxClient / 5 + cxClient / 10, cyClient / 2 - cyClient / 9, "3", 1);
						break;
					}
					case 2:{
						SetTextColor(hdc, RGB(0, 0, 255));
						TextOut(hdc, cxClient / 5 + cxClient / 10, cyClient / 2 - cyClient / 9, "1", 1);
						SetTextColor(hdc, RGB(255, 0, 0));
						TextOut(hdc, 2 * cxClient / 5 + cxClient / 25, cyClient / 2 - cyClient / 9, "Your choise", 11);
						SetTextColor(hdc, RGB(0, 0, 255));
						TextOut(hdc, 3 * cxClient / 5 + cxClient / 10, cyClient / 2 - cyClient / 9, "3", 1);
						break;
					}
					case 3:{
						SetTextColor(hdc, RGB(0, 0, 255));
						TextOut(hdc, cxClient / 5 + cxClient / 10, cyClient / 2 - cyClient / 9, "1", 1);
						TextOut(hdc, 2 * cxClient / 5 + cxClient / 10, cyClient / 2 - cyClient / 9, "2", 1);
						SetTextColor(hdc, RGB(255, 0, 0));
						TextOut(hdc, 3 * cxClient / 5 + cxClient / 25, cyClient / 2 - cyClient / 9, "Your choise", 11);
						SetTextColor(hdc, RGB(0, 0, 255));
						break;
					}
				}
				goto ahead;
			}
			else if(count == 2){
				SelectObject(hdc, hFont);

				bad:
				bonus = rand() % 3 + 1;
				if(bonus == firstChoise)
					goto bad;
				else{
					if(prize[bonus - 1] == 'm')
						goto bad;
					else{
						switch(bonus){
							case 1:{
								Sleep(2000);
								Door(1, cxClient, cyClient, "skate.bmp");
								Sleep(500);
								MessageBox(
									NULL,
									"Aveti posibilitatea sa va schimbati alegerea!",
						            TEXT("Dupa prima usa este scuter!"),
						            MB_ICONEXCLAMATION
								);
								break;
							}
							case 2:{
								Sleep(2000);
								Door(2, cxClient, cyClient, "skate.bmp");
								Sleep(500);
								MessageBox(
									NULL,
									"Aveti posibilitatea sa va schimbati alegerea!",
						            TEXT("Dupa a doua usa este scuter!"),
						            MB_ICONEXCLAMATION
								);
								break;
							}
							case 3:{
								Sleep(2000);
								Door(3, cxClient, cyClient, "skate.bmp");
								Sleep(500);
								MessageBox(
									NULL,
									"Aveti posibilitatea sa va schimbati alegerea!",
						            TEXT("Dupa a treia usa este scuter!"),
						            MB_ICONEXCLAMATION
								);
								break;
							}
						}
					}
				}
				cout << "sasati";
				goto ahead;
			}
			else if(count == 4){
				
				secondChoise = cxBlock;
//				cout << "\nSecond choise = " << secondChoise << endl;
//				if(secondChoise == bonus){
//					MessageBox(
//								NULL,
//								"Usa e deja deschisa",
//					            TEXT("Va rugam sa alege-ti una dintre usile inchise!"),
//					            MB_ICONEXCLAMATION
//							);
//					count--;
//					goto ahead;
//				}
//				else{
					SetBkColor(hdc, RGB(59, 184, 24));
					SelectObject(hdc, hFont);
					switch(secondChoise){
					case 1:{
						if(prize[secondChoise - 1] == 'm'){
							Sleep(1000);
							Door(1, cxClient, cyClient, "car.bmp");
							SetTextColor(hdc, RGB(225, 171, 9));
							TextOut(hdc, cxClient / 5 + cxClient/40, cyClient / 2 - cyClient / 6, "Congratulation!", 15);
							Sleep(500);
							MessageBox(
								NULL,
								"Felicitari! A-ti castigat premiul cel mare",
					            TEXT("Dupa prima usa este masina!"),
					            MB_ICONEXCLAMATION
							);
							
						}
						else{
							Sleep(1000);
							Door(1, cxClient, cyClient, "skate.bmp");
							Sleep(500);
							MessageBox(
								NULL,
								"Felicitari! A-ti castigat un skate",
					            TEXT("Dupa prima usa este skate!"),
					            MB_ICONEXCLAMATION
							);
						}
						break;
					}
					case 2:{
						if(prize[secondChoise - 1] == 'm'){
							Sleep(1000);
							Door(2, cxClient, cyClient, "car.bmp");
							SetTextColor(hdc, RGB(225, 171, 9));
							TextOut(hdc, 2 * cxClient / 5 + cxClient/40, cyClient / 2 - cyClient / 6, "Congratulation!", 15);
							Sleep(500);
							MessageBox(
								NULL,
								"Felicitari! A-ti castigat premiul cel mare",
					            TEXT("Dupa a doua usa este masina!"),
					            MB_ICONEXCLAMATION
							);
							
						}
						else{
							Sleep(1000);
							Door(2, cxClient, cyClient, "skate.bmp");
							Sleep(500);
							MessageBox(
								NULL,
								"Felicitari! A-ti castigat un skate",
					            TEXT("Dupa a doua usa este skate!"),
					            MB_ICONEXCLAMATION
							);
						}
						break;
					}
					case 3:{
						if(prize[secondChoise - 1] == 'm'){
							Sleep(1000);
							Door(3, cxClient, cyClient, "car.bmp");
							SetTextColor(hdc, RGB(225, 171, 9));
							TextOut(hdc, 3 * cxClient / 5 + cxClient/40, cyClient / 2 - cyClient / 6, "Congratulation!", 15);
							Sleep(500);
							MessageBox(
								NULL,
								"Felicitari! A-ti castigat premiul cel mare",
					            TEXT("Dupa a treia usa este masina!"),
					            MB_ICONEXCLAMATION
							);
							
						}
						else{
							Sleep(1000);
							Door(3, cxClient, cyClient, "skate.bmp");
							Sleep(500);
							MessageBox(
								NULL,
								"Felicitari! A-ti castigat un skate",
					            TEXT("Dupa a treia usa este skate!"),
					            MB_ICONEXCLAMATION
							);
						}
						break;
					}
				}
//				}
				
				cout << "Sfirsit";
			}
			
//			else if(firstChoise == 2){
//				
//			}
		
			EndPaint(hwnd, &ps);
			return 0;
		}
		
		case WM_DESTROY :{
			PostQuitMessage(0);
			return 0;
		}
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
