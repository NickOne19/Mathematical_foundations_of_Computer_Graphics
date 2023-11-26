#include "Vector2D.h"

Vector2D::Vector2D(const float& x, const float& y) :
    m_x(x),
    m_y(y)
{
}

void Vector2D::setX(const float& x)
{
    m_x = x;
}

void Vector2D::setY(const float& y)
{
    m_y = y;
}

float Vector2D::x() const
{
    return m_x;
}

float Vector2D::y() const
{
    return m_y;
}
