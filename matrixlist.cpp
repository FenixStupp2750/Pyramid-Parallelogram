#include "matrixlist.h"
#include <iostream>

Matrix multiply(const Matrix& a, const Matrix& b)
{
	Matrix mat;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mat.m[i][j] = 0;
			for (int k = 0; k < 4; k++)
			{
				mat.m[i][j] += a.m[i][k] * b.m[k][j];
			}
		}
	}
	return mat;
}

Matrix getTranslation(double dx, double dy, double dz)
{
	double m[4][4] = { {1, 0, 0, dx},
						{0, 1, 0, dy},
						{0, 0, 1, dz},
						{0, 0, 0, 1} };
	Matrix mat(m);
	return mat;
}

Matrix getScale(double sx, double sy, double sz)
{
	double m[4][4] = { {sx, 0, 0, 0},
						{0, sy, 0, 0},
						{0, 0, sz, 0},
						{0, 0, 0,  1} };
	Matrix mat(m);
	return mat;
}

Matrix getRotationX(double angle)
{
	const double rad = M_PI / 180.0 * angle;
	double m[4][4] = { {1, 0, 0, 0},
						{0, cos(rad), -sin(rad), 0},
						{0, sin(rad), cos(rad), 0},
						{0, 0, 0, 1} };
	Matrix mat(m);
	return mat;
}

Matrix getRotationY(double angle)
{
	const double rad = M_PI / 180.0 * angle;
	double m[4][4] = { {cos(rad), 0, sin(rad), 0},
						{0, 1, 0, 0},
						{-sin(rad), 0, cos(rad), 0},
						{0, 0, 0, 1} };
	Matrix mat(m);
	return mat;
}

Matrix getRotationZ(double angle)
{
	const double rad = M_PI / 180.0 * angle;
	double m[4][4] = { {cos(rad), -sin(rad), 0, 0},
						{sin(rad), cos(rad), 0, 0},
						{0, 0, 1, 0},
						{0, 0, 0, 1} };
	Matrix mat(m);
	return mat;
}

Matrix getLookAt(const Vector3d& eye, const Vector3d& target, const Vector3d& up)
{
	const Vector3d vz = substract(eye, target).normalize();
	const Vector3d vx = crossProduct(up, vz).normalize();
	const Vector3d vy = crossProduct(vz, vx).normalize();

	double m[4][4] = { {vx.x(), vx.y(), vx.z(), 0},
						{vy.x(), vy.y(), vy.z(), 0},
						{vz.x(), vz.y(), vz.z(), 0},
						{0, 0, 0, 1} };
	Matrix mm(m);
	Matrix mat = multiply(mm, getTranslation(-eye.x(), -eye.y(), -eye.z()));
	return mat;
}

Vector3d getShadowX(const Vector3d& l, const Vector3d& p)
{
	Vector3d vec;
	Vector3d line = substract(p, l);
	if (line.x() >= 0)
	{
		vec = Vector3d(-1, -1, -1);
		return vec;
	}
	vec.x() = 0;
	vec.z() = (l.z() * line.x() - l.x() * line.z()) / line.x();
	vec.y() = (l.y() * line.x() - l.x() * line.y()) / line.x();
	return vec;
}

Vector3d getShadowY(const Vector3d& l, const Vector3d& p)
{
	Vector3d vec;
	Vector3d line = substract(p, l);
	if (line.y() >= 0)
	{
		vec = Vector3d(-1, -1, -1);
		return vec;
	}
	vec.y() = 0;
	vec.x() = (l.x() * line.y() - l.y() * line.x()) / line.y();
	vec.z() = (l.z() * line.y() - l.y() * line.z()) / line.y();
	return vec;
}

Vector3d getShadowZ(const Vector3d& l, const Vector3d& p)
{
	Vector3d vec;
	Vector3d line = substract(p, l);
	if (line.z() >= 0)
	{
		vec = Vector3d(-1, -1, -1);
		return vec;
	}
	vec.z() = 0;
	vec.x() = (l.x() * line.z() - l.z() * line.x()) / line.z();
	vec.y() = (l.y() * line.z() - l.z() * line.y()) / line.z();
	return vec;
}

Vector3d checkWallsCollision(const Vector3d& walls, const Vector3d& p)
{
	double d;
	Vector3d res;
	if ((d = p.x() - walls.x()) < 0)
	{
		res.x() = d;
	}
	if ((d = p.y() - walls.y()) < 0)
	{
		res.y() = d;
	}
	if ((d = p.z() - walls.z()) < 0)
	{
		res.z() = d;
	}
	return res;
}