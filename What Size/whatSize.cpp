#include<windows.h>


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstace, PSTR szCmdLine, int iCmdShow)
{
    WNDCLASS wndclass;
    HWND hwnd;
    TCHAR szAppName[] = TEXT("What size");
    MSG msg;

    wndclass.style = CS_VREDRAW | CS_HREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.lpszClassName = szAppName;
    wndclass.lpszMenuName = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;

    if(!RegisterClass(&wndclass))
    {
        MessageBox(NULL, TEXT("This program requires windows NT"), szAppName, iCmdShow);
        return 0;
    }

    hwnd = CreateWindow(szAppName,                  //lpClassName: We need to specify the class name of the window which we create
                        TEXT("Size of Window"),     // Size of the window
                        WS_OVERLAPPEDWINDOW,        // Specifies the window style i.e dwStyle
                        CW_USEDEFAULT,              // x pos
                        CW_USEDEFAULT,              // y pos
                        CW_USEDEFAULT,              // nWidth
                        CW_USEDEFAULT,              // nHeight
                        NULL,                       // Parent Window
                        NULL,                       // Menu since we are using none this should be NULL as in default
                        hInstance,                  // Instance handle
                        NULL                        // Additional application data
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

void Show(HWND hwnd, HDC hdc, int xText, int yText, int iMapMode, TCHAR* szMapMode)
{
    TCHAR szBuffer[60];
    RECT rect;

    SaveDC(hdc);

    SetMapMode(hdc, iMapMode);
    GetClientRect(hwnd, &rect);
    DPtoLP(hdc, (PPOINT)&rect, 2);

    RestoreDC(hdc, -1);

    TextOut(hdc, xText, yText, szBuffer, wsprintf(szBuffer, TEXT("%-20s %7d %7d %7d %7d"), szMapMode, rect.left, rect.right, rect.top, rect.bottom));

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static TCHAR szHeading[] = 
                                TEXT("Mapping mode            Left    Right      Top       Bottom");
    static TCHAR szUndLine[] = 
                                TEXT("------------            ----    -----      ---       ------");
    static int cxChar, cyChar;
    HDC hdc;
    PAINTSTRUCT ps;
    TEXTMETRIC tm;

    switch(message)
    {
        case WM_CREATE:
            hdc = GetDC(hwnd);
            /* This function is used to select an object into the device context DC The new object replaces the previous object of the 
            same type */
            SelectObject(hdc,                                       // Hande to device context
                        GetStockObject(SYSTEM_FIXED_FONT)           // handle to obect to be selected in this case the Stock object
                        );
            
            /* Fille the specified buffer with the metrics for the currently seleted font */
            GetTextMetrics( hdc, &tm);
            cxChar = tm.tmAveCharWidth;
            cyChar = tm.tmHeight + tm.tmExternalLeading;

            ReleaseDC(hwnd, hdc);
            return 0;

        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);
            SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));
            /* Sets mapping mode of any decive context. mode defines the uiny of measure to transform page-
              space  units into device-space unit, also define the orientation of the devices x and y coordinates */
            SetMapMode(hdc, MM_ANISOTROPIC);
            /* Sets horizontal and vertical extents of the windows for a device */
            SetWindowExtEx(hdc, 1, 1, NULL);
            SetViewportExtEx(hdc, cxChar, cyChar, NULL);

            TextOut(hdc, 1, 1, szHeading, lstrlen(szHeading));
            TextOut(hdc, 1, 2, szUndLine, lstrlen(szUndLine));

            Show(hwnd, hdc, 1, 3, MM_TEXT,      TEXT("TEXT (pixels)"));
            Show(hwnd, hdc, 1, 4, MM_LOMETRIC,  TEXT("LOMETRIC (.1 mm)"));
            Show(hwnd, hdc, 1, 5, MM_HIMETRIC,  TEXT("HIMETRIC (.01 mm)"));
            Show(hwnd, hdc, 1, 6, MM_LOENGLISH, TEXT("LOENGLISH (.01 in)"));
            Show(hwnd, hdc, 1, 7, MM_HIENGLISH, TEXT("HIENGLISH (.001 in)"));
            Show(hwnd, hdc, 1, 8, MM_TWIPS,     TEXT("TWIPS (1/1440 in)"));

            EndPaint(hwnd, &ps);
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}
