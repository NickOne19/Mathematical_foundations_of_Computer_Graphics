#ifndef AFFINE_TRANSFORM_H
#define AFFINE_TRANSFORM_H
#include "Matrix.h"

Matrix<double> Translation(double x, double y)
{
	double T[9] = {
		1, 0, x,
		0, 1, y,
		0, 0, 1 };
	return Matrix<double>(3, 3, T);
}

Matrix<double> Rotation(double cosinus, double sinus)
{
	double hypotenuse = sqrt(cosinus * cosinus + sinus * sinus);

	double c = cosinus / hypotenuse;
	double s = sinus / hypotenuse;

	double R[9] = {
		c, s, 0,
		-s, c, 0,
		0, 0, 1 };
	return Matrix<double>(3, 3, R);
}

Matrix<double> Rotation(double rad)
{
	return Rotation(cos(rad), sin(rad));
}

Matrix<double> Scaling(double kx, double ky) {
	double S[9] = {
		kx, 0, 0,
		0, ky, 0,
		0, 0, 1 };
	return Matrix<double>(3, 3, S);
}

Matrix<double> ReflectOX() {
	return Scaling(-1, 1);
}

Matrix<double> ReflectOY() {
	return Scaling(1, -1);
}

#endif AFFINE_TRANSFORM_H
