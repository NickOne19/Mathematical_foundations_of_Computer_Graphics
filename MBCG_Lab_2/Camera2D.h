#pragma once
#include <windows.h>
#include <cmath>
#include "Vector2D.h"
#include "Matrix.h"

class Camera2D
{
public:
	Camera2D() = default;
	Camera2D(HWND window, double X0, double Y0, double px, double py);

	HDC GetDC() const;

	void Clear();

	void MoveTo(double X, double Y);

	void LineTo(double X, double Y);

private:

	// Ёкранные координаты начала мировой системы координат
	double X0, Y0;

	// ≈диницы масштаба мировой системы координат, выраженные в пиксел€х
	double px, py;

	int W, H;

	int WorldToScreenX(double X) const;

	int WorldToScreenY(double Y) const;

	RECT GetDCRect() const;

	int GetScreenWindowWidth() const;

	int GetScreenWindowHeight() const;

private:
	double posX, posY;

	HWND hWindow;
};

