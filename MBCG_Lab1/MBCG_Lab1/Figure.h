#pragma once
#include <wtypes.h>

class Figure
{
public:
	Figure(const int size, const int offsetX, const int offsetY);
	~Figure() = default;

	virtual void draw(const HDC &hdc) = 0;
	virtual bool isInnerPoint(const int x, const int y) = 0;
	virtual void Clear(HDC hdc) = 0;

	void moveTo(const int x, const int y);
	void move(const int x, const int y);

	void startDragging();
	void drag(const int x, const int y);
	bool isDragging() const;
	void stopDragging();

private:
	bool m_isDragging;

protected:
	int m_size;
	int m_offsetX;
	int m_offsetY;
};

