#pragma once
#define _USE_MATH_DEFINES
#include "matrix.h"
#include "vector3d.h"

Matrix multiply(const Matrix& a, const Matrix& b); // умножение матриц

Matrix getTranslation(double dx, double dy, double dz); // матрица переноса

Matrix getScale(double sx, double sy, double sz); // матрица масштаба

Matrix getRotationX(double angle); // матрица поворота вдоль оси X

Matrix getRotationY(double angle); // матрица поворота вдоль оси Y

Matrix getRotationZ(double angle); // матрица поворота вдоль оси Z

Matrix getLookAt(const Vector3d& eye, const Vector3d& target, const Vector3d& up); // матрица камеры

Vector3d getShadowX(const Vector3d& l, const Vector3d& p); // получение тени точки на ось X

Vector3d getShadowY(const Vector3d& l, const Vector3d& p); // получение тени точки на ось Y

Vector3d getShadowZ(const Vector3d& l, const Vector3d& p); // получение тени точки на ось Z

Vector3d checkWallsCollision(const Vector3d& walls, const Vector3d& p); // перенос точки за стену в случае, если она за нее заходит
