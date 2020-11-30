#include<windows.h>
#include<stdlib.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void DrawRectangle(HWND);

int cxClient, cyClient;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("RandRect");
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;

	wndclass.style = CS_VREDRAW | CS_HREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hInstance = hInstance;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires windows NT"), szAppName, MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName, TEXT("Random Rectangle"),
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT, CW_USEDEFAULT,
						CW_USEDEFAULT, CW_USEDEFAULT,
						NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			DrawRectangle(hwnd);
		}
	}
	return msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, iMessage, wParam, lParam);
}

void DrawRectangle(HWND hwnd)
{
	HBRUSH hBrush;
	HDC hdc;
	RECT rect;

	if (cxClient == 1 || cyClient == 0)
	{
		return;
	}

	SetRect(&rect, rand() % cxClient, rand() % cyClient, rand() % cxClient, rand() % cyClient);

	hBrush = CreateSolidBrush(RGB(rand() % 256, rand() %256 , rand() % 256));

	hdc = GetDC(hwnd);

	FillRect(hdc, &rect, hBrush);
	ReleaseDC(hwnd, hdc);
	DeleteObject(hBrush);
}