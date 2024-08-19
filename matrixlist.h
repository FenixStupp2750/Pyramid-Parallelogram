#pragma once
#define _USE_MATH_DEFINES
#include "matrix.h"
#include "vector3d.h"

Matrix multiply(const Matrix& a, const Matrix& b); // ��������� ������

Matrix getTranslation(double dx, double dy, double dz); // ������� ��������

Matrix getScale(double sx, double sy, double sz); // ������� ��������

Matrix getRotationX(double angle); // ������� �������� ����� ��� X

Matrix getRotationY(double angle); // ������� �������� ����� ��� Y

Matrix getRotationZ(double angle); // ������� �������� ����� ��� Z

Matrix getLookAt(const Vector3d& eye, const Vector3d& target, const Vector3d& up); // ������� ������

Vector3d getShadowX(const Vector3d& l, const Vector3d& p); // ��������� ���� ����� �� ��� X

Vector3d getShadowY(const Vector3d& l, const Vector3d& p); // ��������� ���� ����� �� ��� Y

Vector3d getShadowZ(const Vector3d& l, const Vector3d& p); // ��������� ���� ����� �� ��� Z

Vector3d checkWallsCollision(const Vector3d& walls, const Vector3d& p); // ������� ����� �� ����� � ������, ���� ��� �� ��� �������
