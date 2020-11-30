#include<windows.h>
#define SAFE_RELEASE(x) if(x) {CloseHandle(x); x = NULL;}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI ThreadProcOne(LPVOID);
DWORD WINAPI ThreadProcTwo(LPVOID);
void print(HWND);

int i = 0;
HANDLE g_hMutex;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
    TCHAR szAppName[] = TEXT("Thread Program");
    HWND hwnd;
    MSG msg;
    WNDCLASS wndclass;

    wndclass.lpfnWndProc = WndProc;
    wndclass.style = CS_VREDRAW | CS_HREDRAW;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = szAppName;

    if (!RegisterClass(&wndclass))
    {
        MessageBox(NULL, TEXT("This program requires windows NT"), NULL, iCmdShow);
        return 0;
    }

    hwnd = CreateWindow(szAppName, TEXT("Thread Program"),
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

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HANDLE hThreadOne = NULL;
    static HANDLE hThreadTwo = NULL;

    switch (message)
    {
    case WM_CREATE:
        g_hMutex = CreateMutex(NULL, FALSE, NULL);
        hThreadOne = CreateThread(NULL, 0, ThreadProcOne, hwnd, 0, NULL);
        hThreadTwo = CreateThread(NULL, 0, ThreadProcTwo, hwnd, 0, NULL);
        return 0;


    case WM_DESTROY:
        SAFE_RELEASE(hThreadOne);
        SAFE_RELEASE(hThreadTwo);
        SAFE_RELEASE(g_hMutex);
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}

DWORD WINAPI ThreadProcOne(LPVOID lpParam)
{
    DWORD dwRet;
    while (i < 100000)
    {
        dwRet = WaitForSingleObject(g_hMutex, INFINITE);
        switch (dwRet)
        {
        case WAIT_TIMEOUT:
            break;

        case WAIT_OBJECT_0:
            print((HWND)lpParam);
            ReleaseMutex(g_hMutex);
            //Sleep(1000);
            break;
        }

    }
    return 0;
}

DWORD WINAPI ThreadProcTwo(LPVOID lpParam)
{
    DWORD dwRet;
    while (i < 100000)
    {
        dwRet = WaitForSingleObject(g_hMutex, INFINITE);
        switch (dwRet)
        {
        case WAIT_TIMEOUT:
            break;

        case WAIT_OBJECT_0:
            print((HWND)lpParam);
            ReleaseMutex(g_hMutex);
            //Sleep(1000);
            break;
        }
    }
    return 0;
}

void print(HWND hwnd)
{
    HDC hdc;
    TCHAR str[255];
    int iLen = 0, iRetCheck;
    hdc = GetDC(hwnd);
    iLen = wsprintf(str, TEXT("[THREAD %d ]Value of I %d "), GetCurrentThreadId(), i);
    i++;
    iRetCheck = TextOut(hdc, 5, 5, str, iLen);
    ReleaseDC(hwnd, hdc);
}
