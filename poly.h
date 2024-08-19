#pragma once
#define _USE_MATH_DEFINES
#include "vector.h"
#include "vector3d.h"
#include "matrix.h"

class Poly //плоскость или полигон
{
public:
	Poly();
	Poly(vector<Vector3d*> dots);
	Poly(const Poly& copy);
	~Poly();

	void calc_v(); // v - точка, находящаяся внутри плоскости
	Vector3d get_v() const;

	void calc_n(); //n - нормаль к плоскости
	Vector3d get_n() const;

	void add_dot(Vector3d& dot); // добавление точки плоскости
	void clear(); // очищение точки
	void set_dots(vector<Vector3d*> dots); // установка точек плоскости
	Vector3d dot(int i) const; // возвращение i-той точки плоскости

	vector<Vector3d*> get_dots() const; // получение точек плоскости
	int get_len() const; // количество точек плоскости

	bool is_onPoly(double x, double y) const; // проверка нахождения точки на плоскости

private:
	vector<Vector3d*> dots; // массив указателей на точки
	int len; // количество точек
	Vector3d v; // координаты точки на плоскости
	Vector3d n; // нормаль к плоскости
	bool definedflag; // определна ли эта плоскость
};