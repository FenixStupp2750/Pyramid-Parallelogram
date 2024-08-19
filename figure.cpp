#include "figure.h"

Figure::Figure()
{
	len = 0;
}
Figure::Figure(vector<Vector3d*> d, vector<vector<int>> r)
{
	len = 0;
	for (int i = 0, l = d.length(); i < l; i++)
	{
		add_dot(*d[i]);
		add_road(r[i]);
	}
	process_poly();
}
Figure::Figure(const Figure& copy)
{
	len = 0;
	vector<Vector3d*> d = copy.getDots();
	vector<vector<int>> r = copy.getRoads();
	for (int i = 0, l = d.length(); i < l; i++)
	{
		add_dot(*d[i]);
		add_road(r[i]);
	}
	process_poly();

}
Figure::~Figure()
{
	clean();
}

void Figure::copy_dots(const Figure& copy)
{
	vector<Vector3d*> d = copy.getDots();
	for (int i = 0, l = d.length(); i < l; i++)
	{
		add_dot(*d[i]);
	}
}

Figure& Figure::operator= (const Figure& copy)
{
	len = 0;
	vector<Vector3d*> d = copy.getDots();
	vector<vector<int>> r = copy.getRoads();
	for (int i = 0, l = d.length(); i < l; i++)
	{
		add_dot(*d[i]);
	}
	for (int i = 0, l = r.length(); i < l; i++)
	{
		add_road(r[i]);
	}
	return (*this);
}

vector<Vector3d*> Figure::getDots() const
{
	return dots;
}
vector<vector<int>> Figure::getRoads() const
{
	return roads;
}
void Figure::add_dot(Vector3d dot)
{
	Vector3d* d = new Vector3d;
	*d = dot;
	dots.push_back(d);
}
void Figure::add_road(vector<int> road)
{
	roads.push_back(road);
	len = roads.length();
}
void Figure::add_road(int a, int b, int c)
{
	vector<int> r;
	r.push_back(a);
	r.push_back(b);
	r.push_back(c);
	roads.push_back(r);
	len = roads.length();
}
void Figure::add_road(int a, int b, int c, int d)
{
	vector<int> r;
	r.push_back(a);
	r.push_back(b);
	r.push_back(c);
	r.push_back(d);
	roads.push_back(r);
	len = roads.length();
}
int Figure::length()
{
	return len;
}
void Figure::process_poly()
{
	polys.clear();
	Poly p;
	bool skip_dot = false;
	for (int i = 0; i < len; i++)
	{
		skip_dot = false;
		for (int j = 0, l = roads[i].length(); j < l; j++)
		{
			for (int k = 0, t = skip.length(); k < t; k++)
			{
				if (skip[k] == roads[i][j])
				{
					skip_dot = true;
					break;
				}
			}
			if (skip_dot) break;

			p.add_dot(*dots[roads[i][j]]);
		}
		if (!skip_dot)
		{
			polys.push_back(p);
		}
		p.clear();
	}
}
Poly& Figure::get_poly(int i)
{
	return polys[i];
}

void Figure::for_allDots(Vector3d(*op) (const Matrix&, const Vector3d&), const Matrix& m)
{
	for (int i = 0, l = dots.length(); i < l; i++)
	{
		*(dots[i]) = op(m, *dots[i]);
	}
}

void Figure::for_allDots(Vector3d(*op) (const Vector3d&, const Vector3d&), const Vector3d& v)
{
	for (int i = 0, l = dots.length(); i < l; i++)
	{
		*dots[i] = op(v, *dots[i]);
		if ((*dots[i]).x() == -1 && (*dots[i]).y() == -1 && (*dots[i]).z() == -1)
		{
			skip.push_back(i);
		}
	}
}

Vector3d Figure::check_collision(Vector3d walls)
{
	Vector3d res;
	Vector3d buff;
	for (int i = 0, l = dots.length(); i < l; i++)
	{
		buff = checkWallsCollision(walls, *dots[i]);
		res.x() = std::min(res.x(), buff.x());
		res.y() = std::min(res.y(), buff.y());
		res.z() = std::min(res.z(), buff.z());
	}
	return res;
}

Vector3d Figure::get_center()
{
	Vector3d center;
	int l = dots.length();
	center.x() = 0;
	center.y() = 0;
	center.z() = 0;
	for (int i = 0; i < l; i++)
	{
		center.x() += dots[i]->x();
		center.y() += dots[i]->y();
		center.z() += dots[i]->z();
	}
	center.x() /= l;
	center.y() /= l;
	center.z() /= l;
	return center;
}

void Figure::clean()
{
	len = 0;
	polys.clear();
	roads.clear();
	for (int i = 0, l = dots.length(); i < l; i++)
	{
		delete dots[i];
	}
	dots.clear();
}

void Figure::dots_clean()
{
	for (int i = 0, l = dots.length(); i < l; i++)
	{
		delete dots[i];
	}
	dots.clear();
}