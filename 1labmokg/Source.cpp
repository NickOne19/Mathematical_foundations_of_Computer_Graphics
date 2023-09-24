#include <Windows.h>

WNDCLASS createWindowClass(HBRUSH bgColor, HCURSOR cursor, HINSTANCE hInstance, HICON icon, LPCWSTR windowName, WNDPROC windowProcedure);
LRESULT CALLBACK windowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	WNDCLASS mainWindow = createWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInstance, LoadIcon(NULL, IDI_QUESTION), L"MainWndClass", windowProcedure);

	if (!RegisterClassW(&mainWindow))
		return -1;

	CreateWindow(L"MainWndClass", L"MainWindow", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 800, 800, NULL, NULL, NULL, NULL);

	MSG message = { 0 };
	while (GetMessage(&message, NULL, NULL, NULL)) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return 0;
}

WNDCLASS createWindowClass(HBRUSH bgColor, HCURSOR cursor, HINSTANCE hInstance, HICON icon, LPCWSTR windowName, WNDPROC windowProcedure)
{
	WNDCLASS wc = { 0 };

	wc.hCursor = cursor;
	wc.hIcon = icon;
	wc.hInstance = hInstance;
	wc.lpszClassName = windowName;
	wc.hbrBackground = bgColor;
	wc.lpfnWndProc = windowProcedure;

	return wc;
}

LRESULT CALLBACK windowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    HDC hdc = NULL;

    static POINT pt;
    int n = 10;
    const static int len = 50;
    static RECT rcClient;
    GetClientRect(hWnd, &rcClient);
    static RECT circle;
    static int clr = 0;
    COLORREF colors[]{ RGB(255,0,0), RGB(0,255,0), RGB(0,0,255), RGB(0,0,0), RGB(255,255,255) };

    switch (msg)
    {
    case WM_CREATE:
        pt.x = rcClient.right / 2;
        pt.y = rcClient.bottom / 2;
        circle.left = pt.x - len / 2;
        circle.top = pt.y - len / 2;
        circle.right = pt.x + len / 2;
        circle.bottom = pt.y + len / 2;
        break;

    case WM_LBUTTONDOWN:
        if (circle.right - circle.left > n * 2 && circle.bottom - circle.top > n * 2)
        {
            // Уменьшение размеров окружности
            circle.left += n;
            circle.top += n;
            circle.right -= n;
            circle.bottom -= n;

            // Обновление окна
            InvalidateRect(hWnd, NULL, true);
            UpdateWindow(hWnd);
        }
        break;

    case WM_RBUTTONDOWN:
        // Увеличение размеров окружности
        circle.left -= n;
        circle.top -= n;
        circle.right += n;
        circle.bottom += n;

        // Обновление окна
        InvalidateRect(hWnd, NULL, true);
        UpdateWindow(hWnd);
        break;

    case WM_KEYDOWN:
        if (wp == 0x43) // Если нажата клавиша 'C'
        {
            clr = (clr + 1) % 5; // Изменение цвета окружности

            // Обновление окна
            InvalidateRect(hWnd, NULL, true);
            UpdateWindow(hWnd);
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        hdc = BeginPaint(hWnd, &ps);

        HBRUSH hBrush = CreateSolidBrush(colors[clr]);
        HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

        Ellipse(hdc, circle.left, circle.top, circle.right, circle.bottom);

        SelectObject(hdc, hOldBrush);
        DeleteObject(hBrush);

        EndPaint(hWnd, &ps);
        break;
    }

    default:
        return DefWindowProc(hWnd, msg, wp, lp);
    }

    return 0;
}
