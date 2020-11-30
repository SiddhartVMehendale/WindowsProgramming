#include<windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	TCHAR szAppName[] = TEXT("Key Font");
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;

	wndclass.style = CS_VREDRAW | CS_HREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("The program requires Windows NT"), szAppName, MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName, TEXT("Key Font"),
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
	static DWORD dwCharSet = DEFAULT_CHARSET;
	static int cxClientMax, cyClientMax, cxClient, cyClient, cxChar, cyChar;
	static int cLinesMax, cLines;
	static PMSG pmsg;
	static RECT rectScroll;
	static TCHAR szTop[] =	TEXT("Message		Key			Char	")
							TEXT("Repaet  Scan  Exit  Prev  Temp");
							
	static TCHAR szUnd[] =  TEXT("_______		___			____")
							TEXT("______  ____  ____  ____  ____");

	static TCHAR* szFormat[2] = {
								(TCHAR*)TEXT("%-13s %3d %-15s%c%6u %4d %3s %3s %4s %4s"),
								(TCHAR*)TEXT("%-13s			0x%04X%1s%c  %6u %4d %3s  %3s %3s  %4s  %4s")
								};

	static TCHAR* szYes = (TCHAR*)TEXT("Yes");
	static TCHAR* szNo = (TCHAR*)TEXT("No");
	static TCHAR* szDown = (TCHAR*)TEXT("Down");
	static TCHAR* szUp = (TCHAR*)TEXT("Up");
	
	static TCHAR* szMessage[] = {
							(TCHAR*)TEXT("WM_KEYDOWN"), (TCHAR*)TEXT("WM_KEYDOWN"),
							(TCHAR*)TEXT("WM_CHAR"),	(TCHAR*)TEXT("WM_DEADCHAR"),
							(TCHAR*)TEXT("WM_SYSKEYDOWN"),(TCHAR*)TEXT("WM_SYSKEYUP"),
							(TCHAR*)TEXT("WM_SYSCHAR"),	(TCHAR*)TEXT("WM_SYSDEADCHAR") };

	HDC hdc;
	int i, iType;
	PAINTSTRUCT ps;
	TCHAR szBuffer[128], szKeyName[32];
	TEXTMETRIC tm;

	switch(iMessage)
	{
	case WM_INPUTLANGCHANGE:
		dwCharSet = wParam;

	case WM_CREATE:
	case WM_DISPLAYCHANGE:
		// get maximum size of the client area
		cxClientMax = GetSystemMetrics(SM_CXMAXIMIZED);
		cyClientMax = GetSystemMetrics(SM_CYMAXIMIZED);

		// Get character size for fixed-pitch font
		hdc = GetDC(hwnd);

		SelectObject(hdc, CreateFont(0, 0, 0, 0, 0, 0, 0, 0, dwCharSet, 0, 0, 0, FIXED_PITCH, NULL));

		GetTextMetrics(hdc, &tm);
		cxChar = tm.tmAveCharWidth;
		cyChar = tm.tmHeight;

		DeleteObject(SelectObject (hdc, GetStockObject(SYSTEM_FONT)));
		ReleaseDC(hwnd, hdc);
		
		// Allocate memory for display lines
		if (pmsg)
		{
			free(pmsg);
		}
		cLinesMax = cyClientMax / cyChar;
		pmsg = (PMSG)malloc(cLinesMax * sizeof(MSG));
		cLines = 0;
		// fall through

	case WM_SIZE:	
		if (iMessage == WM_SIZE)
		{
			cxClient = LOWORD(lParam);
			cyClient = HIWORD(lParam);
		}
		// Callculate scrolling rectangle

		rectScroll.left = 0;
		rectScroll.right = cxClient;
		rectScroll.top = cyChar;
		rectScroll.bottom = cyChar * (cyClient / cyChar);

		InvalidateRect(hwnd, NULL, TRUE);

		if (iMessage == WM_INPUTLANGCHANGE)
		{
			return TRUE;
		}
		return 0;

	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_CHAR:
	case WM_DEADCHAR:
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
	case WM_SYSCHAR:
	case WM_SYSDEADCHAR:
		// Rearrage storage array
		
		for (i = cLinesMax - 1; i > 0; i--)
		{
			pmsg[i] = pmsg[i - 1];
		}
		// Store new message

		pmsg[0].hwnd = hwnd;
		pmsg[0].message = iMessage;
		pmsg[0].wParam = wParam;
		pmsg[0].lParam = lParam;

		cLines = min(cLines + 1, cLinesMax);
		// Scroll up display 

		ScrollWindow(hwnd, 0, -cyChar, &rectScroll, &rectScroll);
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		SelectObject(hdc, CreateFont(0, 0, 0, 0, 0, 0, 0, 0, dwCharSet, 0, 0, 0, FIXED_PITCH, NULL));
		
		SetBkMode(hdc, TRANSPARENT);
		TextOut(hdc, 0, 0, szTop, lstrlen(szTop));
		TextOut(hdc, 0, 0, szUnd, lstrlen(szUnd));

		for (i = 0; i < min(cLines, cyClient / cyChar - 1); i++)
		{
			iType = pmsg[i].message == WM_CHAR || pmsg[i].message == WM_SYSCHAR || pmsg[i].message == WM_DEADCHAR || pmsg[i].message == WM_SYSDEADCHAR;

			GetKeyNameText(pmsg[i].lParam, szKeyName, sizeof(szKeyName) / sizeof(TCHAR));

			TextOut(hdc, 0, (cyClient / cyChar - 1 -i) * cyChar, szBuffer, wsprintf(szBuffer, szFormat[iType], szMessage[pmsg[i].message - WM_KEYFIRST],
					pmsg[i].wParam,
					(PSTR)(iType ? TEXT(" "): szKeyName),
					(TCHAR)(iType ? pmsg[i].wParam : ' '),
					LOWORD(pmsg[i].lParam),
					HIWORD(pmsg[i].lParam) & 0xFF,
					0x01000000 & pmsg[i].lParam ? szYes : szNo,
					0x20000000 & pmsg[i].lParam ? szYes : szNo,
					0x40000000 & pmsg[i].lParam ? szDown : szUp,
					0x80000000 & pmsg[i].lParam ? szUp : szDown));
		}
		DeleteObject(SelectObject(hdc, GetStockObject(SYSTEM_FONT)));
		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, iMessage, wParam, lParam);
}