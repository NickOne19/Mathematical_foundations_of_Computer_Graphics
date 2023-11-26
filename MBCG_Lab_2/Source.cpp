#include <Windows.h>
#include <windowsx.h>
#include "Loader.h"
#include "Render2D.h"
#include "AffineTransform.h"
#include <map>

#define M_PI (3.14159265358979323846)

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

Loader loader_1("1.txt");
Loader loader_2("2.txt");
Loader loader_3("3.txt");

Model2D model = Model2D(loader_1.vertices(), loader_1.indices());
Model2D model_2 = Model2D(loader_2.vertices(), loader_2.indices());
Model2D model_3 = Model2D(loader_3.vertices(), loader_3.indices());

Model2D models[3] = { model, model_2, model_3 };

Render2D render;
std::map<HWND, Camera2D> windows;

int index_model = 0;

LRESULT CALLBACK windowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	const char KEY_X = 0x58;
	const char KEY_Y = 0x59;
	const char KEY_Q = 0x51;
	const char KEY_E = 0x45;
	const char KEY_C = 0x43;

	Camera2D camera = windows[hWnd];
	HDC hdc = NULL;

	switch (msg)
	{
	case WM_CREATE:
		windows[hWnd] = Camera2D(hWnd, 350, 325, 50, 50);
		render.addObject(&models[0]);
		render.addObject(&models[1]);
		render.addObject(&models[2]);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
	{
		windows[hWnd].Clear();
		render.draw(hdc, windows[hWnd]);
		ReleaseDC(hWnd, windows[hWnd].GetDC());
		return DefWindowProc(hWnd, msg, wp, lp);
	}
	case WM_MOUSEWHEEL:
	{
		if (GET_WHEEL_DELTA_WPARAM(wp) > 0)
			models[index_model].transform(Scaling(1.5, 1.5));
		else
			models[index_model].transform(Scaling(0.75, 0.75));
		InvalidateRect(hWnd, nullptr, false);
	}
	case WM_KEYDOWN:
	{
		switch (wp)
		{
		case VK_UP:
		{
			models[index_model].transform(Translation(0, 0.5));
			break;
		}
		case VK_DOWN:
		{
			models[index_model].transform(Translation(0, -0.5));
			break;
		}
		case VK_LEFT:
		{
			models[index_model].transform(Translation(-0.5, 0));
			break;
		}
		case VK_RIGHT:
		{
			models[index_model].transform(Translation(0.5, 0));
			break;
		}
		case KEY_X:
		{
			auto point_start = models[index_model].getPoint(0);
			auto point_end = models[index_model].getPoint(1);

			models[index_model].transform(Translation(-point_start.x(), -point_start.y()))
				.transform(Rotation(point_end.x() - point_start.x(), point_end.y() - point_start.y()))
				.transform(ReflectOX())
			    .transform(Rotation(point_start.x() - point_end.x(), point_start.y() - point_end.y()))
				.transform(Translation(point_start.x(), point_start.y()));

			break;
		}
		case KEY_Y:
		{
			auto point_start = models[index_model].getPoint(0);
			auto point_end = models[index_model].getPoint(1);

			models[index_model].transform(Translation(-point_start.x(), -point_start.y()))
				.transform(Rotation(point_end.x() - point_start.x(), point_end.y() - point_start.y()))
				.transform(ReflectOY())
				.transform(Rotation(point_start.x() - point_end.x(), point_start.y() - point_end.y()))
				.transform(Translation(point_start.x(), point_start.y()));

			break;
		}
		case KEY_Q:
		{
			auto point = models[index_model].getPoint(0);
			models[index_model].transform(Translation(-point.x(), -point.y()))
				.transform(Rotation(-M_PI / 4))
				.transform(Translation(point.x(), point.y()));
			break;
		}
		case KEY_E:
		{
			auto point = models[index_model].getPoint(0);
			models[index_model].transform(Translation(-point.x(), -point.y()))
				.transform(Rotation(M_PI / 4))
				.transform(Translation(point.x(), point.y()));
			break;
		}
		case KEY_C:
		{
			index_model += 1;
			if (index_model == 3)
				index_model = 0;
			break;
		}
		}
		InvalidateRect(hWnd, NULL, false);
		return 0;
	}
	default:
		return DefWindowProc(hWnd, msg, wp, lp);
	}
}
