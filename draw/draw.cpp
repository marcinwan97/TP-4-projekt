// draw.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "draw.h"
#include <string>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

struct klocek
{
	int masa = 10;
	int x;
	int y;
	HBRUSH kolor;
};
klocek pierwszy;
klocek drugi;
klocek trzeci;
klocek* zlapany = NULL;

int x = 350;					//	zawsze parzyste
int y = 301;					//	zawsze nieparzyste
int udzwig = 10;

HWND hwndButton;
HBITMAP htlo = (HBITMAP)LoadImage(NULL, L"tlo.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hbudowa = (HBITMAP)LoadImage(NULL, L"budowa.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

RECT masy = { 710, 70, 750, 400 };

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
bool moznaodczepic(struct klocek* zlapany);

void MyOnPaint(HDC hdc)
{
	Graphics graphics(hdc);
	Pen penczarny(Color(255, 0, 0, 0));
	Pen penR(Color(255, 77, 0, 0));
	Pen penG(Color(0, 77, 26));
	Pen penB(Color(0, 19, 77));
	SolidBrush brush(Color(255, 0, 0, 0));
	SolidBrush brushR(Color(255, 230, 0, 0));
	SolidBrush brushG(Color(255, 0, 179, 0));
	SolidBrush brushB(Color(255, 0, 0, 204));
	Font font(L"Arial", 20);
	HBRUSH czarny = CreateSolidBrush(RGB(0, 00, 0));
	HBRUSH hak = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH budowa = CreatePatternBrush(hbudowa);
	RECT dzwig1 = { x - 10, 50, x + 10, 60 };
	RECT dzwig2 = { x - 10, y - 10, x + 10, y + 1 };
	RECT dzwig3 = { 20, 485, 90, 520 };
	RECT klocek1 = { pierwszy.x, pierwszy.y, pierwszy.x + 100, pierwszy.y + 100 };
	RECT klocek2 = { drugi.x, drugi.y, drugi.x + 100, drugi.y + 100 };
	RECT klocek3 = { trzeci.x, trzeci.y, trzeci.x + 100, trzeci.y + 100 };
	RECT tlo1 = { 20, 10, 670, 520 };


	FillRect(hdc, &tlo1, budowa);															//	wypelnianie tla

	graphics.DrawLine(&penczarny, x, 59, x, y - 10);										//	lina i ramka
	graphics.DrawRectangle(&penczarny, 20, 10, 650, 510);
	graphics.DrawRectangle(&penczarny, 19, 9, 652, 512);

	std::wstring tempstring = std::to_wstring(pierwszy.masa);								//	wyswietlanie mas klockow
	const wchar_t* tempchar = tempstring.c_str();
	PointF point1a(710, 25);
	graphics.DrawString(L"Masa czerwonego klocka:", -1, &font, point1a, &brushR);
	PointF point1b(710, 70);
	graphics.DrawString(tempchar, -1, &font, point1b, &brushR);

	tempstring = std::to_wstring(drugi.masa);											
	tempchar = tempstring.c_str();
	PointF point2a(710, 125);
	graphics.DrawString(L"Masa zielonego klocka:", -1, &font, point2a, &brushG);
	PointF point2b(710, 170);
	graphics.DrawString(tempchar, -1, &font, point2b, &brushG);

	tempstring = std::to_wstring(trzeci.masa);											
	tempchar = tempstring.c_str();
	PointF point3a(710, 225);
	graphics.DrawString(L"Masa niebieskiego klocka:", -1, &font, point3a, &brushB);
	PointF point3b(710, 270);
	graphics.DrawString(tempchar, -1, &font, point3b, &brushB);

	tempstring = std::to_wstring(udzwig);
	tempchar = tempstring.c_str();
	PointF point4a(710, 325);
	graphics.DrawString(L"UdŸwig:", -1, &font, point4a, &brush);
	PointF point4b(710, 370);
	graphics.DrawString(tempchar, -1, &font, point4b, &brush);

	if (x >= pierwszy.x + 39 && x <= pierwszy.x + 61 && y == pierwszy.y - 1 && pierwszy.masa <= udzwig)		//	zmiana koloru haka
		hak = CreateSolidBrush(RGB(221, 170, 28));
	if (x >= drugi.x + 39 && x <= drugi.x + 61 && y == drugi.y - 1 && drugi.masa <= udzwig)
		hak = CreateSolidBrush(RGB(221, 170, 28));
	if (x >= trzeci.x + 39 && x <= trzeci.x + 61 && y == trzeci.y - 1 && trzeci.masa <= udzwig)
		hak = CreateSolidBrush(RGB(221, 170, 28));
	if (zlapany != NULL) hak = CreateSolidBrush(RGB(168, 11, 0));
	if (zlapany != NULL && moznaodczepic(zlapany)) hak = CreateSolidBrush(RGB(221, 170, 28));

	FillRect(hdc, &dzwig1, czarny);																			//	wypelnienie elementow dzwigu
	FillRect(hdc, &dzwig2, hak);
	FillRect(hdc, &dzwig3, czarny);
	FillRect(hdc, &klocek1, pierwszy.kolor);																//	rysowanie klockow i wzoru na nich
	graphics.DrawRectangle(&penR, pierwszy.x, pierwszy.y, 99, 99);
	graphics.DrawRectangle(&penR, pierwszy.x + 1, pierwszy.y + 1, 97, 97);
	graphics.DrawLine(&penR, pierwszy.x, pierwszy.y, pierwszy.x + 99, pierwszy.y + 99);
	graphics.DrawLine(&penR, pierwszy.x, pierwszy.y + 1, pierwszy.x + 98, pierwszy.y + 99);
	graphics.DrawLine(&penR, pierwszy.x + 99, pierwszy.y, pierwszy.x, pierwszy.y + 99);
	graphics.DrawLine(&penR, pierwszy.x + 99, pierwszy.y + 1, pierwszy.x + 1, pierwszy.y + 99);
	FillRect(hdc, &klocek2, drugi.kolor);
	graphics.DrawRectangle(&penG, drugi.x, drugi.y, 99, 99);
	graphics.DrawRectangle(&penG, drugi.x + 1, drugi.y + 1, 97, 97);
	graphics.DrawLine(&penG, drugi.x, drugi.y, drugi.x + 99, drugi.y + 99);
	graphics.DrawLine(&penG, drugi.x, drugi.y + 1, drugi.x + 98, drugi.y + 99);
	graphics.DrawLine(&penG, drugi.x + 99, drugi.y, drugi.x, drugi.y + 99);
	graphics.DrawLine(&penG, drugi.x + 99, drugi.y + 1, drugi.x + 1, drugi.y + 99);
	FillRect(hdc, &klocek3, trzeci.kolor);
	graphics.DrawRectangle(&penB, trzeci.x, trzeci.y, 99, 99);
	graphics.DrawRectangle(&penB, trzeci.x + 1, trzeci.y + 1, 97, 97);
	graphics.DrawLine(&penB, trzeci.x, trzeci.y, trzeci.x + 99, trzeci.y + 99);
	graphics.DrawLine(&penB, trzeci.x, trzeci.y + 1, trzeci.x + 98, trzeci.y + 99);
	graphics.DrawLine(&penB, trzeci.x + 99, trzeci.y, trzeci.x, trzeci.y + 99);
	graphics.DrawLine(&penB, trzeci.x + 99, trzeci.y + 1, trzeci.x + 1, trzeci.y + 99);
}

void repaintWindow(HWND hWnd, HDC &hdc, PAINTSTRUCT &ps, RECT *drawArea)
{
	if (drawArea == NULL)
		InvalidateRect(hWnd, drawArea, TRUE); //	repaint all
	else
		InvalidateRect(hWnd, drawArea, TRUE); //	repaint drawArea
	hdc = BeginPaint(hWnd, &ps);
	MyOnPaint(hdc);
	EndPaint(hWnd, &ps);
}

bool kolizjahak(struct klocek sprawdzany, struct klocek* zlapany, char klawisz)
{
	if (zlapany != NULL) return false;					//	by nie blokowaæ opuszczania zlapanego klocka
	if (klawisz == 's' && x >= sprawdzany.x - 9 && x <= sprawdzany.x + 109 && y >= sprawdzany.y - 1 && y < sprawdzany.y + 99) return true;
	if (klawisz == 'w' && x >= sprawdzany.x - 9 && x <= sprawdzany.x + 109 && y == sprawdzany.y + 109) return true;
	if (klawisz == 'a' && x == sprawdzany.x + 110 && y >= sprawdzany.y && y <= sprawdzany.y + 108) return true;
	if (klawisz == 'a' && y >= sprawdzany.y + 109 && x == sprawdzany.x + 100) return true;
	if (klawisz == 'd' && x == sprawdzany.x - 10 && y >= sprawdzany.y && y <= sprawdzany.y + 108) return true;
	if (klawisz == 'd' && y >= sprawdzany.y + 109 && x == sprawdzany.x - 2) return true;
	else return false;
}

bool kolizjaklocka(struct klocek* zlapany, char klawisz)
{
	if (zlapany == NULL) return false;			//	ta funkcja obejmuje tylko kolizje zlapanego klocka z innym klockiem
	if (klawisz == 's' && zlapany->y + 100 == pierwszy.y && zlapany->x >= pierwszy.x - 98 && zlapany->x <= pierwszy.x + 98) return true;	//	kolizja z dolu
	if (klawisz == 's' && zlapany->y + 100 == drugi.y && zlapany->x >= drugi.x - 98 && zlapany->x <= drugi.x + 98) return true;
	if (klawisz == 's' && zlapany->y + 100 == trzeci.y && zlapany->x >= trzeci.x - 98 && zlapany->x <= trzeci.x + 98) return true;
	if (klawisz == 's' && zlapany->y == 420) return true;																					//	kolizja z podlozem
	if (klawisz == 'a' && zlapany->x == pierwszy.x + 100 && zlapany->y >= pierwszy.y - 98 && zlapany->y <= pierwszy.y + 100) return true;	//	kolizja z lewej
	if (klawisz == 'a' && zlapany->x == drugi.x + 100 && zlapany->y >= drugi.y - 98 && zlapany->y <= drugi.y + 100) return true;
	if (klawisz == 'a' && zlapany->x == trzeci.x + 100 && zlapany->y >= trzeci.y - 98 && zlapany->y <= trzeci.y + 100) return true;
	if (klawisz == 'd' && zlapany->x + 100 == pierwszy.x && zlapany->y >= pierwszy.y - 98 && zlapany->y <= pierwszy.y + 100) return true;	//	kolizja z prawej
	if (klawisz == 'd' && zlapany->x + 100 == drugi.x && zlapany->y >= drugi.y - 98 && zlapany->y <= drugi.y + 100) return true;
	if (klawisz == 'd' && zlapany->x + 100 == trzeci.x && zlapany->y >= trzeci.y - 98 && zlapany->y <= trzeci.y + 100) return true;
	return false;
}

bool moznaodczepic(struct klocek* zlapany)
{
	if (kolizjaklocka(zlapany, 's') || zlapany->y == 420)
	{
		if (zlapany->y == 420) return true;
		else if (zlapany->kolor != drugi.kolor && zlapany->x >= drugi.x - 22 && zlapany->x <= drugi.x + 22) return true;
		else if (zlapany->kolor != trzeci.kolor && zlapany->x >= trzeci.x - 22 && zlapany->x <= trzeci.x + 22) return true;
		else if (zlapany->kolor != pierwszy.kolor && zlapany->x >= pierwszy.x - 22 && zlapany->x <= pierwszy.x + 22) return true;
		else return false;
	}
	else return false;
}

int OnCreate(HWND window)
{
	pierwszy.x = 140;
	pierwszy.y = 420;
	pierwszy.kolor = CreateSolidBrush(RGB(230, 0, 0));
	drugi.x = 340;
	drugi.y = 420;
	drugi.kolor = CreateSolidBrush(RGB(0, 179, 0));
	trzeci.x = 540;
	trzeci.y = 420;
	trzeci.kolor = CreateSolidBrush(RGB(0, 0, 204));
	SetWindowText(window, L"Zad. 4.4 - Marcin Wankiewicz, Kacper Wojciechowski, Bartosz S³owiñski");
   return 0;
}



int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DRAW, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DRAW));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	GdiplusShutdown(gdiplusToken);

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DRAW));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(CreatePatternBrush(htlo));
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_DRAW);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX,	//	blokada mozliwosci maksymalizacji i skalowania okna
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
   
   hwndButton = CreateWindow(TEXT("button"), TEXT("Zwiêksz"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 770, 65, 80, 40, hWnd, (HMENU)ID_BUTTON1, hInstance, NULL);
   hwndButton = CreateWindow(TEXT("button"), TEXT("Zmniejsz"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 870, 65, 80, 40, hWnd, (HMENU)ID_BUTTON2, hInstance, NULL);

   hwndButton = CreateWindow(TEXT("button"), TEXT("Zwiêksz"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 770, 165, 80, 40, hWnd, (HMENU)ID_BUTTON3, hInstance, NULL);
   hwndButton = CreateWindow(TEXT("button"), TEXT("Zmniejsz"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 870, 165, 80, 40, hWnd, (HMENU)ID_BUTTON4, hInstance, NULL);

   hwndButton = CreateWindow(TEXT("button"), TEXT("Zwiêksz"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 770, 265, 80, 40, hWnd, (HMENU)ID_BUTTON5, hInstance, NULL);
   hwndButton = CreateWindow(TEXT("button"), TEXT("Zmniejsz"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 870, 265, 80, 40, hWnd, (HMENU)ID_BUTTON6, hInstance, NULL);

   hwndButton = CreateWindow(TEXT("button"), TEXT("Zwiêksz"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 770, 365, 80, 40, hWnd, (HMENU)ID_BUTTON7, hInstance, NULL);
   hwndButton = CreateWindow(TEXT("button"), TEXT("Zmniejsz"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 870, 365, 80, 40, hWnd, (HMENU)ID_BUTTON8, hInstance, NULL);

   hwndButton = CreateWindow(TEXT("button"), TEXT("Reset"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1000, 460, 100, 40, hWnd, (HMENU)ID_BUTTON9, hInstance, NULL);

   OnCreate(hWnd);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	RECT lina = { x - 13, 50, x + 13, y + 3 };								//	prostokaty do odswiezania, ktore skaluja sie w zaleznosci od potrzeby
	if(zlapany != NULL) lina = { x - 13, 50, x + 13, y + 1 };
	RECT podniesiony = { x - 64, y-1, x + 64, y + 103 };

	//OnCreate(hWnd,wParam,lParam);
	//OnTimer(hWnd,wParam,lParam);

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_BUTTON1:													//	masa czerwonego
			if(pierwszy.masa<99) pierwszy.masa++;
			repaintWindow(hWnd, hdc, ps, &masy);
			repaintWindow(hWnd, hdc, ps, &lina);
			SetFocus(hWnd);													//	aby nie blokowac klawiatury, 'oddaje' focus na glowne okno
			break;
		case ID_BUTTON2:
			if (pierwszy.masa>1) pierwszy.masa--;
			repaintWindow(hWnd, hdc, ps, &masy);
			repaintWindow(hWnd, hdc, ps, &lina);
			SetFocus(hWnd);
			break;
		case ID_BUTTON3:													//	masa zielonego
			if (drugi.masa<99) drugi.masa++;
			repaintWindow(hWnd, hdc, ps, &masy);
			repaintWindow(hWnd, hdc, ps, &lina);
			SetFocus(hWnd);
			break;
		case ID_BUTTON4:
			if (drugi.masa>1) drugi.masa--;
			repaintWindow(hWnd, hdc, ps, &masy);
			repaintWindow(hWnd, hdc, ps, &lina);
			SetFocus(hWnd);
			break;
		case ID_BUTTON5:													//	masa niebieskiego
			if (trzeci.masa<99) trzeci.masa++;
			repaintWindow(hWnd, hdc, ps, &masy);
			repaintWindow(hWnd, hdc, ps, &lina);
			SetFocus(hWnd);
			break;
		case ID_BUTTON6:
			if (trzeci.masa>1) trzeci.masa--;
			repaintWindow(hWnd, hdc, ps, &masy);
			repaintWindow(hWnd, hdc, ps, &lina);
			SetFocus(hWnd);
			break;
		case ID_BUTTON7:													//	udzwig
			if (udzwig<99) udzwig++;
			repaintWindow(hWnd, hdc, ps, &masy);
			repaintWindow(hWnd, hdc, ps, &lina);
			SetFocus(hWnd);
			break;
		case ID_BUTTON8:
			if (udzwig>1) udzwig--;			
			repaintWindow(hWnd, hdc, ps, &masy);
			repaintWindow(hWnd, hdc, ps, &lina);
			SetFocus(hWnd);
			break;
		case ID_BUTTON9:													//	reset
			pierwszy.masa = drugi.masa = trzeci.masa = udzwig = 10; 
			pierwszy.y = drugi.y = trzeci.y = 420; 
			pierwszy.x = 140; 
			drugi.x = 340;
			trzeci.x = 540;
			zlapany = NULL;
			x = 350; 
			y = 301; 
			EnableWindow(GetDlgItem(hWnd, ID_BUTTON1), true);
			EnableWindow(GetDlgItem(hWnd, ID_BUTTON2), true);
			EnableWindow(GetDlgItem(hWnd, ID_BUTTON3), true);
			EnableWindow(GetDlgItem(hWnd, ID_BUTTON4), true);
			EnableWindow(GetDlgItem(hWnd, ID_BUTTON5), true);
			EnableWindow(GetDlgItem(hWnd, ID_BUTTON6), true);
			EnableWindow(GetDlgItem(hWnd, ID_BUTTON7), true);
			EnableWindow(GetDlgItem(hWnd, ID_BUTTON8), true);
			repaintWindow(hWnd, hdc, ps, NULL);
			SetFocus(hWnd);
		break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case 0x57:	 // w
			if (y > 80 && !kolizjahak(pierwszy, zlapany, 'w') && !kolizjahak(drugi, zlapany, 'w') && !kolizjahak(trzeci, zlapany, 'w'))
			{
				y -= 2;
				if (zlapany != NULL) zlapany->y -= 2;
			}
			repaintWindow(hWnd, hdc, ps, &lina);
			if (zlapany != NULL) repaintWindow(hWnd, hdc, ps, &podniesiony);
			break;
		case 0x53:	// s
			if (y < 460 && !kolizjahak(pierwszy, zlapany, 's') && !kolizjahak(drugi, zlapany, 's') && !kolizjahak(trzeci, zlapany, 's') && !kolizjaklocka(zlapany, 's'))
			{
				y += 2;
				if (zlapany != NULL) zlapany->y += 2;
			}
			repaintWindow(hWnd, hdc, ps, &lina);
			if (zlapany != NULL) repaintWindow(hWnd, hdc, ps, &podniesiony);
			break;
		case 0x41:    // a
			if (x > 160 && !kolizjahak(pierwszy, zlapany, 'a') && !kolizjahak(drugi, zlapany, 'a') && !kolizjahak(trzeci, zlapany, 'a') && !kolizjaklocka(zlapany, 'a'))
			{
				x -= 2;
				if (zlapany != NULL) zlapany->x -= 2;
			}
			repaintWindow(hWnd, hdc, ps, &lina);
			if (zlapany != NULL) repaintWindow(hWnd, hdc, ps, &podniesiony);
			break;
		case 0x44:   // d
			if (x < 600 && !kolizjahak(pierwszy, zlapany, 'd') && !kolizjahak(drugi, zlapany, 'd') && !kolizjahak(trzeci, zlapany, 'd') && !kolizjaklocka(zlapany, 'd'))
			{
				x += 2;
				if (zlapany != NULL) zlapany->x += 2;
			}
			repaintWindow(hWnd, hdc, ps, &lina);
			if (zlapany != NULL) repaintWindow(hWnd, hdc, ps, &podniesiony);
			break;
		case VK_SPACE:
			if (zlapany == NULL)
			{
				if (x >= pierwszy.x + 39 && x <= pierwszy.x + 61 && y == pierwszy.y - 1 && pierwszy.masa <= udzwig)		//	czy mozna podniesc czerwony?
				{
					zlapany = &pierwszy;
					EnableWindow(GetDlgItem(hWnd, ID_BUTTON1), false);		//	blokada zmiany masy podniesionego klocka i udzwigu
					EnableWindow(GetDlgItem(hWnd, ID_BUTTON2), false);
					EnableWindow(GetDlgItem(hWnd, ID_BUTTON7), false);
					EnableWindow(GetDlgItem(hWnd, ID_BUTTON8), false);
					repaintWindow(hWnd, hdc, ps, &lina);
				}
				if (x >= drugi.x + 39 && x <= drugi.x + 61 && y == drugi.y - 1 && drugi.masa <= udzwig)		//	czy mozna podniesc zielony?
				{
					zlapany = &drugi;
					EnableWindow(GetDlgItem(hWnd, ID_BUTTON3), false);
					EnableWindow(GetDlgItem(hWnd, ID_BUTTON4), false);
					EnableWindow(GetDlgItem(hWnd, ID_BUTTON7), false);
					EnableWindow(GetDlgItem(hWnd, ID_BUTTON8), false);
					repaintWindow(hWnd, hdc, ps, &lina);
				}
				if (x >= trzeci.x + 39 && x <= trzeci.x + 61 && y == trzeci.y - 1 && trzeci.masa <= udzwig)		//	czy mozna podniesc niebieski?
				{
					zlapany = &trzeci;
					EnableWindow(GetDlgItem(hWnd, ID_BUTTON5), false);
					EnableWindow(GetDlgItem(hWnd, ID_BUTTON6), false);
					EnableWindow(GetDlgItem(hWnd, ID_BUTTON7), false);
					EnableWindow(GetDlgItem(hWnd, ID_BUTTON8), false);
					repaintWindow(hWnd, hdc, ps, &lina);
				}
			}
			else
			{
				if (zlapany != NULL && moznaodczepic(zlapany))				//	jesli cos zlapane, to czy mozna to odczepic?
				{
					zlapany = NULL;
					EnableWindow(GetDlgItem(hWnd, ID_BUTTON1), true);		//	odblokowanie wszystkich przyciskow
					EnableWindow(GetDlgItem(hWnd, ID_BUTTON2), true);
					EnableWindow(GetDlgItem(hWnd, ID_BUTTON3), true);
					EnableWindow(GetDlgItem(hWnd, ID_BUTTON4), true);
					EnableWindow(GetDlgItem(hWnd, ID_BUTTON5), true);
					EnableWindow(GetDlgItem(hWnd, ID_BUTTON6), true);
					EnableWindow(GetDlgItem(hWnd, ID_BUTTON7), true);
					EnableWindow(GetDlgItem(hWnd, ID_BUTTON8), true);
					repaintWindow(hWnd, hdc, ps, &lina);
				}
			}
			break;
		}
	}
	break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		MyOnPaint(hdc);
		EndPaint(hWnd, &ps);
		break;
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
