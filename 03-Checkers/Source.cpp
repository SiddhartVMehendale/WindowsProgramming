#include<windows.h>

#define DIVISIONS 5

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildWndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szChildClass[] = TEXT("Checker3_Child");

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	TCHAR szAppName[] = TEXT("CHECKER3");
	MSG msg;
	WNDCLASS wndclass;
	HWND hwnd;

	wndclass.style = CS_VREDRAW | CS_HREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.hInstance = hInstance;
	wndclass.lpszMenuName = NULL;
	wndclass.lpfnWndProc = WndProc;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires windows NT"), szAppName, MB_ICONERROR);
		return 0;
	}

	wndclass.lpfnWndProc = ChildWndProc;
	wndclass.cbWndExtra = sizeof(long);
	wndclass.hIcon = NULL;
	wndclass.lpszClassName = szChildClass;

	RegisterClass(&wndclass);

	hwnd = CreateWindow(szAppName, TEXT("Checkers3 Mouse hit test"),
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

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	static HWND hwndChild[DIVISIONS][DIVISIONS];
	int cxBlock, cyBlock, x, y;

	switch (iMessage)
	{
	case WM_CREATE:
		for (x = 0; x < DIVISIONS; x++)
		{
			for (y = 0; y < DIVISIONS; y++)
			{
				hwndChild[x][y] = CreateWindow(szChildClass, NULL,
					WS_CHILDWINDOW | WS_VISIBLE | WS_OVERLAPPEDWINDOW,
					0, 0, 0, 0,
					hwnd, (HMENU)(y << 8 | x),
					(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
			}
		}
		return 0;

	case WM_SIZE:
		cxBlock = LOWORD(lParam) / DIVISIONS;
		cyBlock = HIWORD(lParam) / DIVISIONS;

		for (x = 0; x < DIVISIONS; x++)
		{
			for (y = 0; y < DIVISIONS; y++)
			{
				MoveWindow(hwndChild[x][y], x * cxBlock, y * cyBlock, cxBlock, cyBlock, TRUE);
			}
		}

	case WM_LBUTTONDOWN:
		MessageBeep(0);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMessage, wParam, lParam);
}

LRESULT CALLBACK ChildWndProc(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;

	switch (iMessage)
	{
	case WM_CREATE:
		SetWindowLong(hwnd, 0, 0);
		return 0;

	case WM_LBUTTONDOWN:
		SetWindowLong(hwnd, 0, 1 ^ GetWindowLong(hwnd, 0));
		InvalidateRect(hwnd, NULL, FALSE);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		
		GetClientRect(hwnd, &rect);
		Rectangle(hdc, 0, 0, rect.right, rect.bottom);

		if (GetWindowLong(hwnd, 0))
		{
			MoveToEx(hdc, 0, 0, NULL);
			LineTo(hdc, rect.right, rect.bottom);
			MoveToEx(hdc, 0, rect.bottom, NULL);
			LineTo(hdc, rect.right, NULL);
		}
		EndPaint(hwnd, &ps);
		return 0;
	}
	return DefWindowProc(hwnd, iMessage, wParam, lParam);
}