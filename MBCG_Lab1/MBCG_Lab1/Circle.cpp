#include "Circle.h"

Circle::Circle(const int size, const int offsetX, const int offsetY) :
    Figure(size, offsetX, offsetY)
{
}

void Circle::Clear(HDC dc)
{
    RECT r;
    GetClientRect(WindowFromDC(dc), &r);
    Rectangle(dc, 0, 0, r.right, r.bottom);
}

void Circle::draw(const HDC& hdc)
{
    Ellipse(hdc, m_offsetX - m_size, m_offsetY - m_size, m_offsetX + m_size, m_offsetY + m_size);
}

bool Circle::isInnerPoint(const int x, const int y)
{
    return (x - m_offsetX) * (x - m_offsetX) + (y - m_offsetY) * (y - m_offsetY) <= m_size * m_size;
}
