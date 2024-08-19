#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include "poly.h"
#include "matrixlist.h"

class Figure
{
public:
	Figure();
	Figure(vector<Vector3d*> d, vector<vector<int>> r);
	Figure(const Figure& copy);
	~Figure();

	void copy_dots(const Figure& copy); // копирование точек другой фигуры

	Figure& operator= (const Figure& copy); // копирование фигуры

	vector<Vector3d*> getDots() const; // получение точек фигуры
	vector<vector<int>> getRoads() const; // получение связей фигуры

	void add_dot(Vector3d dot); // добавление точки
	void add_road(vector<int> road); // добавление связей точек
	void add_road(int a, int b, int c);
	void add_road(int a, int b, int c, int d);
	int length(); // возвращение количества плоскостей фигуры
	void process_poly(); // создание плоскостей фигуры
	Poly& get_poly(int i); // возвращение полигона

	void for_allDots(Vector3d(*op) (const Matrix&, const Vector3d&), const Matrix& m); // применение функции с матрицей для каждой точки
	void for_allDots(Vector3d(*op) (const Vector3d&, const Vector3d&), const Vector3d& v); // применение функции с вектором для каждой точки
	Vector3d check_collision(Vector3d walls); // перемещние фигуры для предотвращения ее нахождения за стеной

	Vector3d get_center(); // центр фигуры

	void clean(); // очистка полей фигуры
	void dots_clean(); // очистка точек фигуры

private:
	vector<Poly> polys;
	vector<vector<int>> roads;
	vector<int> skip;
	vector<Vector3d*> dots;
	int len;

};
