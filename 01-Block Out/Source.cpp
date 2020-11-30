#include<windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR iCmdLine, int iCmdShow)
{
	TCHAR szAppName[] = TEXT("Blokout");
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;

	wndclass.style = CS_VREDRAW | CS_HREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This progrma requiers Windows NT to execute"), szAppName, MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName, TEXT("BlokOut"),
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT, CW_USEDEFAULT,
						CW_USEDEFAULT, CW_USEDEFAULT,
						NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
		
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

void DrawBoxOutline(HWND hwnd, POINT ptBeg, POINT ptEnd)
{
	HDC hdc;
	hdc = GetDC(hwnd);
	
	SetROP2(hdc, R2_NOT);
	SelectObject(hdc, GetStockObject(NULL_BRUSH));
	Rectangle(hdc, ptBeg.x, ptBeg.y, ptEnd.x, ptEnd.y);

	ReleaseDC(hwnd, hdc);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	static BOOL fBlocking, fValidBox;
	static POINT ptBeg, ptEnd, ptBoxBeg, ptBoxEnd;
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{

	case WM_LBUTTONDOWN:
		ptBeg.x = ptEnd.x = LOWORD(lParam);
		ptBeg.y = ptEnd.y = HIWORD(lParam);
		
		DrawBoxOutline(hwnd, ptBeg, ptEnd);
		SetCursor(LoadCursor(NULL, IDC_CROSS));

		fBlocking = TRUE;
		return 0;

	case WM_MOUSEMOVE:
		if (fBlocking)
		{
			SetCursor(LoadCursor(NULL, IDC_CROSS));

			DrawBoxOutline(hwnd, ptBeg, ptEnd);

			ptEnd.x = LOWORD(lParam);
			ptEnd.y = HIWORD(lParam);

			DrawBoxOutline(hwnd, ptBeg, ptEnd);
		}
		return 0;

	case WM_LBUTTONUP:
		if (fBlocking)
		{
			DrawBoxOutline(hwnd, ptBeg, ptEnd);

			ptBoxBeg = ptBeg;
			ptBoxEnd.x = LOWORD(lParam);
			ptBoxEnd.y = HIWORD(lParam);

			SetCursor(LoadCursor(NULL, IDC_ARROW));
			fBlocking = FALSE;
			fValidBox = TRUE;

			InvalidateRect(hwnd, NULL, TRUE);
		}
		return 0;

	case WM_CHAR:
		if (fBlocking & wParam == '\x1B')
		{
			DrawBoxOutline(hwnd, ptBeg, ptEnd);

			SetCursor(LoadCursor(NULL,	IDC_ARROW));

			fBlocking = FALSE;
		}
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		
		if (fValidBox)
		{
			SelectObject(hdc, GetStockObject(BLACK_BRUSH));
			Rectangle(hdc, ptBoxBeg.x, ptBoxBeg.y, ptBoxEnd.x, ptBoxEnd.y);
		}
		if (fBlocking)
		{
			SetROP2(hdc, R2_NOT);
			SelectObject(hdc, GetStockObject(NULL_BRUSH));
			Rectangle(hdc, ptBeg.x, ptBeg.y, ptEnd.x, ptEnd.y);
		}
		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, iMessage, wParam, lParam);
}