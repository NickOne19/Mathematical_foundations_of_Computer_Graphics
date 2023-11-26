#include "Model2D.h"
#include <windef.h>
#include <wingdi.h>
#include <windowsx.h>

Model2D::Model2D(const std::vector<Vector2D>& vertices, const std::vector<int> indices) :
    m_vertices(vertices),
    m_indices(indices)
{
    double T[9] = {
        1, 0, 0,
        0, 1, 0,
        0, 0, 1 };
    m_modelMatrix = Matrix<>(3, 3, T);

}

Vector2D Model2D::transformPoint(Vector2D point)
{
    Matrix<> pointMatrix(3, 1);
    pointMatrix(1, 1) = point.x();
    pointMatrix(2, 1) = point.y();
    pointMatrix(3, 1) = 1;

    Matrix<> transformedPointMatrix = m_modelMatrix * pointMatrix;

    double x_transformed = transformedPointMatrix(1, 1);
    double y_transformed = transformedPointMatrix(2, 1);

    Vector2D transformedPoint(x_transformed, y_transformed);

    return transformedPoint;
}

void Model2D::draw(const HDC& hdc, Camera2D& camera)
{
    for (size_t i = 0; i < m_indices.size() - 1; i++)
    {

        Vector2D fpoint = transformPoint(m_vertices[m_indices[i]]);

        Vector2D spoint = transformPoint(m_vertices[m_indices[i + 1]]);
        camera.MoveTo(fpoint.x(), fpoint.y());
        camera.LineTo(spoint.x(), spoint.y());
    }
}

Model2D& Model2D::transform(Matrix<> T)
{
    m_modelMatrix = T * m_modelMatrix;
    return *this;
}

Vector2D Model2D::getPoint(int index)
{
    if (index < m_indices.size() && index > -1) {
        return transformPoint(m_vertices[m_indices[index]]);
    }
}