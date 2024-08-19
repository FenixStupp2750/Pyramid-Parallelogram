#pragma once
#define _USE_MATH_DEFINES
#include "vector.h"
#include "vector3d.h"
#include "matrix.h"

class Poly //��������� ��� �������
{
public:
	Poly();
	Poly(vector<Vector3d*> dots);
	Poly(const Poly& copy);
	~Poly();

	void calc_v(); // v - �����, ����������� ������ ���������
	Vector3d get_v() const;

	void calc_n(); //n - ������� � ���������
	Vector3d get_n() const;

	void add_dot(Vector3d& dot); // ���������� ����� ���������
	void clear(); // �������� �����
	void set_dots(vector<Vector3d*> dots); // ��������� ����� ���������
	Vector3d dot(int i) const; // ����������� i-��� ����� ���������

	vector<Vector3d*> get_dots() const; // ��������� ����� ���������
	int get_len() const; // ���������� ����� ���������

	bool is_onPoly(double x, double y) const; // �������� ���������� ����� �� ���������

private:
	vector<Vector3d*> dots; // ������ ���������� �� �����
	int len; // ���������� �����
	Vector3d v; // ���������� ����� �� ���������
	Vector3d n; // ������� � ���������
	bool definedflag; // ��������� �� ��� ���������
};