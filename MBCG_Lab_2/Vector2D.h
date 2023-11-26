#pragma once

class Vector2D
{
public:
	Vector2D() = default;
	Vector2D(const float& x, const float& y);

	void setX(const float& x);
	void setY(const float& y);

	float x() const;
	float y() const;

private:
	float m_x = 0.0;
	float m_y = 0.0;
};