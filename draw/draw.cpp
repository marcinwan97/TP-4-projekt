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
	int masa=10;
	int x;
	int y;
	HBRUSH kolor;
};

klocek pierwszy;
klocek drugi;
klocek trzeci;

klocek* zlapany = NULL;

int x=300;
int y=151; 

HWND hwndButton;

RECT masy = { 710, 70, 750, 300 };
RECT pole = { 100, 55, 670, 520 };


// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);


void MyOnPaint(HDC hdc)
{
	Graphics graphics(hdc);
	Pen pen(Color(255, 0, 0, 0));
	SolidBrush brush(Color(255, 15, 30, 110));
	SolidBrush brushR(Color(255, 255, 50, 50));
	SolidBrush brushG(Color(255, 50, 255, 50));
	SolidBrush brushB(Color(255, 50, 50, 255));

	Font font(L"Arial", 20);
	HBRUSH hbrush = CreateSolidBrush(RGB(100, 100, 100));

	RECT dzwig1 = { 60, 20, 100, 520 };
	RECT dzwig2 = { 30, 20, 650, 55 };
	RECT dzwig3 = { x - 10, y - 10, x + 10, y+1 };
	RECT klocek1 = { pierwszy.x, pierwszy.y, pierwszy.x + 100, pierwszy.y + 100 };
	RECT klocek2 = { drugi.x, drugi.y, drugi.x + 100, drugi.y + 100 };
	RECT klocek3 = { trzeci.x, trzeci.y, trzeci.x+100, trzeci.y+100 };

	graphics.DrawLine(&pen, x, 40, x, y);
	


	graphics.DrawRectangle(&pen, 20, 10, 650, 510);

	std::wstring tempstring = std::to_wstring(pierwszy.masa);								// wyswietlanie mas klockow
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


	FillRect(hdc, &dzwig1, hbrush);
	FillRect(hdc, &dzwig2, hbrush);
	FillRect(hdc, &dzwig3, hbrush);
	FillRect(hdc, &klocek1, pierwszy.kolor);
	FillRect(hdc, &klocek2, drugi.kolor);
	FillRect(hdc, &klocek3, trzeci.kolor);
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

bool kolizjagora(struct klocek sprawdzany)
{
	if (x >= sprawdzany.x - 9 && x <= sprawdzany.x + 109 && y > sprawdzany.y - 1 && y < sprawdzany.y + 99) return true;
	else return false;
}

bool kolizjadol(struct klocek sprawdzany)
{
	if (x >= sprawdzany.x - 9 && x <= sprawdzany.x + 109 && y == sprawdzany.y + 109) return true;
	else return false;
}

bool kolizjalewa(struct klocek sprawdzany)
{
	if (x == sprawdzany.x + 110 && y >= sprawdzany.y && y <= sprawdzany.y + 108) return true;
	if (y >= sprawdzany.y + 109 && x == sprawdzany.x + 100) return true;
	else return false;
}

bool kolizjaprawa(struct klocek sprawdzany)
{
	if (x == sprawdzany.x - 10 && y >= sprawdzany.y && y <= sprawdzany.y + 108) return true;
	if (y >= sprawdzany.y + 109 && x == sprawdzany.x - 2) return true;
	else return false;
}

int OnCreate(HWND window)
{
	pierwszy.x = 140;
	pierwszy.y = 420;
	pierwszy.kolor = CreateSolidBrush(RGB(250, 100, 100));
	drugi.x = 340;
	drugi.y = 420;
	drugi.kolor = CreateSolidBrush(RGB(100, 250, 100));
	trzeci.x = 540;
	trzeci.y = 420;
	trzeci.kolor = CreateSolidBrush(RGB(100, 100, 250));
	SetWindowText(window, L"Zad 4.4 - Marcin Wankiewicz, Kacper Wojciechowski, Bartosz S³owiñski");
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
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
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

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
   
   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
	   TEXT("Zwieksz"),                  // the caption of the button
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
	   770, 65,                                  // the left and top co-ordinates
	   80, 40,                              // width and height
	   hWnd,                                 // parent window handle
	   (HMENU)ID_BUTTON1,                   // the ID of your button
	   hInstance,                            // the instance of your application
	   NULL);                               // extra bits you dont really need

   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
	   TEXT("Zmniejsz"),                  // the caption of the button
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
	   870, 65,                                  // the left and top co-ordinates
	   80, 40,                              // width and height
	   hWnd,                                 // parent window handle
	   (HMENU)ID_BUTTON2,                   // the ID of your button
	   hInstance,                            // the instance of your application
	   NULL);                               // extra bits you dont really need

   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
	   TEXT("Zwieksz"),                  // the caption of the button
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
	   770, 165,                                  // the left and top co-ordinates
	   80, 40,                              // width and height
	   hWnd,                                 // parent window handle
	   (HMENU)ID_BUTTON3,                   // the ID of your button
	   hInstance,                            // the instance of your application
	   NULL);                               // extra bits you dont really need

   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
	   TEXT("Zmniejsz"),                  // the caption of the button
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
	   870, 165,                                  // the left and top co-ordinates
	   80, 40,                              // width and height
	   hWnd,                                 // parent window handle
	   (HMENU)ID_BUTTON4,                   // the ID of your button
	   hInstance,                            // the instance of your application
	   NULL);                               // extra bits you dont really need

   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
	   TEXT("Zwieksz"),                  // the caption of the button
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
	   770, 265,                                  // the left and top co-ordinates
	   80, 40,                              // width and height
	   hWnd,                                 // parent window handle
	   (HMENU)ID_BUTTON5,                   // the ID of your button
	   hInstance,                            // the instance of your application
	   NULL);                               // extra bits you dont really need

   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
	   TEXT("Zmniejsz"),                  // the caption of the button
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
	   870, 265,                                  // the left and top co-ordinates
	   80, 40,                              // width and height
	   hWnd,                                 // parent window handle
	   (HMENU)ID_BUTTON6,                   // the ID of your button
	   hInstance,                            // the instance of your application
	   NULL);                               // extra bits you dont really need

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
		case ID_BUTTON1:
			if(pierwszy.masa<99) pierwszy.masa++;
			repaintWindow(hWnd, hdc, ps, &masy);
			SetFocus(hWnd);
			break;
		case ID_BUTTON2:
			if (pierwszy.masa>1) pierwszy.masa--;
			repaintWindow(hWnd, hdc, ps, &masy);
			SetFocus(hWnd);
			break;
		case ID_BUTTON3:
			if (drugi.masa<99) drugi.masa++;
			repaintWindow(hWnd, hdc, ps, &masy);
			SetFocus(hWnd);
			break;
		case ID_BUTTON4:
			if (drugi.masa>1) drugi.masa--;
			repaintWindow(hWnd, hdc, ps, &masy);
			SetFocus(hWnd);
			break;
		case ID_BUTTON5:
			if (trzeci.masa<99) trzeci.masa++;
			repaintWindow(hWnd, hdc, ps, &masy);
			SetFocus(hWnd);
			break;
		case ID_BUTTON6:
			if (trzeci.masa>1) trzeci.masa--;
			repaintWindow(hWnd, hdc, ps, &masy);
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
		case 0x57:    // w
			if (y > 80 && !kolizjadol(pierwszy) && !kolizjadol(drugi) && !kolizjadol(trzeci))
			{
				y -= 2;
				if (zlapany != NULL) zlapany->y -= 2;
			}
			repaintWindow(hWnd, hdc, ps, &pole);
			break;
		case 0x53:    // s
			if (y < 418 && !kolizjagora(pierwszy) && !kolizjagora(drugi) && !kolizjagora(trzeci))
			{
				y += 2;
				if (zlapany != NULL) zlapany->y += 2;
			}
			repaintWindow(hWnd, hdc, ps, &pole);
			break;
		case 0x41:    // a
			if (x > 150 && !kolizjalewa(pierwszy) && !kolizjalewa(drugi) && !kolizjalewa(trzeci))
			{
				x -= 2;
				if (zlapany != NULL) zlapany->x -= 2;
			}
			repaintWindow(hWnd, hdc, ps, &pole);
			break;
		case 0x44:   // d
			if (x < 600 && !kolizjaprawa(pierwszy) && !kolizjaprawa(drugi) && !kolizjaprawa(trzeci))
			{
				x += 2;
				if (zlapany != NULL) zlapany->x += 2;
			}
			repaintWindow(hWnd, hdc, ps, &pole);
			break;
		case VK_SPACE:
			if (zlapany == NULL)
			{
				if (x >= pierwszy.x + 35 && x <= pierwszy.x + 65 && y == pierwszy.y - 1) zlapany = &pierwszy;
				if (x >= drugi.x + 35 && x <= drugi.x + 65 && y == drugi.y - 1) zlapany = &drugi;
				if (x >= trzeci.x + 35 && x <= trzeci.x + 65 && y == trzeci.y - 1) zlapany = &trzeci;
			}
			else
			{
				zlapany = NULL;
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
