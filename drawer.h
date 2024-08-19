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

	void draw_dot(double x, double y, int color, const Poly& p); // ���������� �����
	int get_dot(double x, double y); // �������� ���� �����
	void draw_line(double x1, double y1, double x2, double y2, int color, const Poly& p); // ���������� �����
	double z_buff_get_pix(double x, double y, const Poly& p); // �������� �������� z ��� �����
	void fill_z_buff(const Poly& p); // ��������� z-������ �� ���������
	void fill(double x, double y, int color, int bordercolor, const Poly& p); // ��������� ��������� ������� ��������� � ���������
	void draw_poly(const Poly& p, int color, int colorborders, bool fillflag = true); // ���������� ���������

	void clean(); // ������� z-�������
private:
	int width; // ������ ����
	int height; // ������ ����
	double** z_buff; // z-������
};