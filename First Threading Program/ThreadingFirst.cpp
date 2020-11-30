#include<windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI zProcOne(LPVOID); 
DWORD WINAPI zProcTwo(LPVOID);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hprevInstance, PSTR szCmdLine, int iCmdShow)
{
	static WCHAR szAppName[] = TEXT("Hello windows");
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT"), szAppName, MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName,
		TEXT("The Hello world program"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);
	ShowWindow(hwnd, SW_SHOWMAXIMIZED);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;
	static HANDLE hThreadOne = NULL;
	static HANDLE hThreadTwo = NULL;

	switch (message)
	{
	case WM_CREATE:
		hThreadOne = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)zProcOne, (LPVOID)hwnd, 0, NULL);
		hThreadTwo = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)zProcTwo, (LPVOID)hwnd, 0, NULL);
		//PlaySound(TEXT("hellowin.wav"), NULL, SND_FILENAME | SND_ASYNC);
		return 0;

	case WM_LBUTTONDOWN:
		MessageBox(hwnd, TEXT("This is a multi threaded application"), TEXT("Message"), MB_OK);
		break;


	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		GetClientRect(hwnd, &rect);

		DrawText(hdc, TEXT("Hello, this is windows 10"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY:
		if (hThreadOne)
		{
			CloseHandle(hThreadOne);
			hThreadOne = NULL;
		}
		if (hThreadTwo)
		{
			CloseHandle(hThreadTwo);
			hThreadTwo = NULL;
		}
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);

}

DWORD WINAPI zProcOne(LPVOID Param)
{
	HDC hdc;
	int i;
	TCHAR str[255];

	hdc = GetDC((HWND)Param);

	for (i = 0; i < 3768; i++)
	{
		wsprintf(str, TEXT("%d"),i);
		TextOut(hdc, 5, 5, str, wcslen(str));
	}

	ReleaseDC((HWND)Param, hdc);

	return 0;
}

DWORD WINAPI zProcTwo(LPVOID Param)
{
	HDC hdc;
	int i;
	TCHAR str[255];

	hdc = GetDC((HWND)Param);

	for (i = 32768; i > 0; i--)
	{
		wsprintf(str, TEXT("%d"), i);
		TextOut(hdc, 5, 5, str, wcslen(str));
	}

	ReleaseDC((HWND)Param, hdc);

	return 0;
}











