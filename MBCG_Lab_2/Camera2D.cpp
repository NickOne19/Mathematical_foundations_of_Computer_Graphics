#include "Camera2D.h"

Camera2D::Camera2D(HWND hWindow, double X0, double Y0, double px, double py) : hWindow(hWindow), X0(X0), Y0(Y0), px(px), py(py)
{
	MoveTo(X0, Y0);
	W = GetScreenWindowWidth();
	H = GetScreenWindowHeight();
}

HDC Camera2D::GetDC() const
{
	return ::GetDC(hWindow);
}

void Camera2D::Clear()
{
	RECT rect = GetDCRect();
	Rectangle(GetDC(), rect.left, rect.top, rect.right, rect.bottom);
}

void Camera2D::MoveTo(double X, double Y)
{
	posX = X;
	posY = Y;
}

void Camera2D::LineTo(double X, double Y)
{
	HDC hdc = GetDC();

	MoveToEx(hdc, WorldToScreenX(posX), WorldToScreenY(posY), nullptr);
	::LineTo(hdc, WorldToScreenX(X), WorldToScreenY(Y));

	posX = X;
	posY = Y;
}

int Camera2D::WorldToScreenX(double X) const
{
	return (int)round(X0 + px * X);
}

int Camera2D::WorldToScreenY(double Y) const
{
	return (int)round(Y0 - py * Y);
}

RECT Camera2D::GetDCRect() const
{
	RECT rect;
	GetClientRect(hWindow, &rect);
	return rect;
}

int Camera2D::GetScreenWindowWidth() const
{
	RECT rect = GetDCRect();
	return rect.right - rect.left;
}

int Camera2D::GetScreenWindowHeight() const
{
	RECT rect = GetDCRect();
	return rect.bottom - rect.top;
}

