#pragma once
#define _USE_MATH_DEFINES
#include <cmath>

class Matrix // матрица
{
public:
	double m[4][4];
	Matrix();
	Matrix(double m[4][4]);
	Matrix(const Matrix& copy);
	void set_ones(); // матрица с единицами на главной диагонали
	~Matrix();
};