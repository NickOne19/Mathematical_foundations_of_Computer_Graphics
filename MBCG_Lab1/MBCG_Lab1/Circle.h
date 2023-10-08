#pragma once

#include "Figure.h"

class Circle : public Figure
{
public:
	Circle(const int size = 10, const int offsetX = 100, const int offsetY = 100);

	void Clear(HDC);
	void draw(const HDC& hdc) override;
	bool isInnerPoint(const int x, const int y) override;
};

