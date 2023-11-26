#pragma once
#include <windows.h>
#include <vector>
#include "Vector2D.h"
#include "Matrix.h"
#include "Camera2D.h"

class Model2D
{
public:
	Model2D() = default;
	Model2D(const std::vector<Vector2D>& vertices, const std::vector<int> indices);

	Vector2D transformPoint(Vector2D point);
	void draw(const HDC& hdc, Camera2D& camera);
	Model2D& transform(Matrix<> T);
	Vector2D getPoint(int index);
private:
	std::vector<Vector2D> m_vertices;
	std::vector<int> m_indices;

	Matrix<> m_modelMatrix;
protected:
	COLORREF color;
};
