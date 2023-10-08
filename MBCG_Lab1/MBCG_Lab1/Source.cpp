#include <Windows.h>
#include <windowsx.h>
#include "Circle.h"

Figure& circle = *(new Circle(30));

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
	static POINT pt, point_next;

	switch (msg)
	{
	case WM_CREATE:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		hdc = GetDC(hWnd);
		circle.Clear(hdc);
		SelectObject(hdc, GetStockObject(DC_BRUSH));
		SetDCBrushColor(hdc, RGB(255, 0, 0));
		circle.draw(hdc);
		ReleaseDC(hWnd, hdc);
		return DefWindowProc(hWnd, msg, wp, lp);
		break;
	case WM_MOUSEMOVE:
		if (circle.isDragging())
		{
			GetCursorPos(&point_next);
			ScreenToClient(hWnd, &point_next);
			circle.drag(point_next.x, point_next.y);
			InvalidateRect(hWnd, nullptr, false);
		}
		break;
	case WM_LBUTTONUP:
		circle.stopDragging();
		break;
	case WM_LBUTTONDOWN:
		GetCursorPos(&pt);
		ScreenToClient(hWnd, &pt);
		if (!circle.isInnerPoint(pt.x, pt.y)) {
			circle.move(pt.x, pt.y);
			InvalidateRect(hWnd, nullptr, false);
		}
		else
		{
			circle.startDragging();
		}
		break;
	default:
		return DefWindowProc(hWnd, msg, wp, lp);
	}
}
