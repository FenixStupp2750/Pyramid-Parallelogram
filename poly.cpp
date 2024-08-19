#include "poly.h"

Poly::Poly()
{
	len = 0;
	definedflag = false;

}
Poly::Poly(vector<Vector3d*> dots)
{
	this->dots = dots;
	definedflag = true;
	calc_v();
	calc_n();
	len = dots.length();
}
Poly::Poly(const Poly& copy)
{
	this->dots = copy.get_dots();
	definedflag = true;
	calc_v();
	calc_n();
	len = dots.length();
}
Poly::~Poly() {};

void Poly::calc_v()
{
	if (!definedflag)
	{
		return;
	}
	Vector3d vec((*dots[0]).x(), (*dots[0]).y(), (*dots[0]).z());
	this->v = vec;
}
Vector3d Poly::get_v() const
{
	if (!definedflag)
	{
		throw;
	}
	return v;
}

void Poly::calc_n()
{
	if (!definedflag)
	{
		return;
	}
	Vector3d v1 = *(dots[0]);
	Vector3d v2 = *(dots[1]);
	Vector3d v3 = *(dots[2]);

	Vector3d t1 = substract(v1, v2);
	Vector3d t2 = substract(v2, v3);

	Vector3d nor = crossProduct(t1, t2);
	this->n = nor;
}

Vector3d Poly::get_n() const
{
	if (!definedflag)
		throw;
	return n;
}

void Poly::add_dot(Vector3d& dot)
{
	dots.push_back(&dot);
	len = dots.length();
	if (len >= 3)
	{
		definedflag = true;
		calc_n();
		calc_v();
		return;
	}
	definedflag = false;
}

void Poly::clear()
{
	definedflag = false;
	dots.clear();
}

void Poly::set_dots(vector<Vector3d*> dots)
{
	this->dots = dots;
	len = dots.length();
	if (len >= 3)
	{
		definedflag = true;
		calc_n();
		calc_v();
		return;
	}
	definedflag = false;
}

Vector3d Poly::dot(int i) const
{
	if (definedflag)
	{
		return *(dots[i]);
	}
	throw;
}

vector<Vector3d*> Poly::get_dots() const
{
	return dots;
}
int Poly::get_len() const
{
	return len;
}

bool Poly::is_onPoly(double x, double y) const
{
	int numLinesFromLeft = 0;
	int numLinesFromRight = 0;

	for (int i = 0, j = 1; i < len; i++, j = (i + 1) % len) {

		if (((*dots[i]).y() < y && (*dots[j]).y() < y) ||
			((*dots[i]).y() > y && (*dots[j]).y() > y))
			continue;

		double lineX = ((y - (*dots[i]).y()) / ((*dots[j]).y() - (*dots[i]).y()) * ((*dots[j]).x() - (*dots[i]).x())) + (*dots[i]).x();

		if (lineX < x)
			numLinesFromRight++;
		else
			numLinesFromLeft++;
	}

	if (0 < numLinesFromLeft && 0 < numLinesFromRight && numLinesFromLeft == numLinesFromRight)
		return true;
	return false;
}