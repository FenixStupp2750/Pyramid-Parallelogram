#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <limits>
#include "faststack.h"
#include "vector.h"
#include "matrix.h"
#include "vector3d.h"
#include "poly.h"

#include "graphics.h"
#pragma comment(lib,"graphics.lib")

class Drawer
{
public:
	Drawer();
	Drawer(int width, int height);
	~Drawer();

	void draw_dot(double x, double y, int color, const Poly& p); // нарисовать точку
	int get_dot(double x, double y); // получить цвет точки
	void draw_line(double x1, double y1, double x2, double y2, int color, const Poly& p); // нарисовать линию
	double z_buff_get_pix(double x, double y, const Poly& p); // получить значение z для точки
	void fill_z_buff(const Poly& p); // заполнить z-буффер по плоскости
	void fill(double x, double y, int color, int bordercolor, const Poly& p); // заполнить плоскость методом зарисовки с затравкой
	void draw_poly(const Poly& p, int color, int colorborders, bool fillflag = true); // нарисовать плоскость

	void clean(); // очистка z-буффера
private:
	int width; // ширина окна
	int height; // высота окна
	double** z_buff; // z-буффер
};