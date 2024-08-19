#include "drawer.h"
Drawer::Drawer()
{
	this->width = 600;
	this->height = 600;
#ifdef BUFF_DRAWER
	initwindow(600, 600, "3dfigure", 0, 0, true);
#else
	initwindow(600, 600, "3dfigure", 0, 0, false);
#endif
	setbkcolor(WHITE);
	cleardevice();
	swapbuffers();
	z_buff = new double* [height];
	for (int i = 0; i < height; i++)
	{
		z_buff[i] = new double[width];
		for (int j = 0; j < width; j++)
		{
			z_buff[i][j] = INT_MIN;
		}
	}
}

Drawer::Drawer(int width, int height)
{
	this->width = width;
	this->height = height;
#ifdef BUFF_DRAWER
	initwindow(width, height, "3dfigure", 0, 0, true);
#else
	initwindow(width, height, "3dfigure", 0, 0, false);
#endif
	setbkcolor(WHITE);
	cleardevice();
	z_buff = new double* [width];
	for (int i = 0; i < width; i++)
	{
		z_buff[i] = new double[height];
		for (int j = 0; j < height; j++)
		{
			z_buff[i][j] = INT_MIN;
		}
	}
}
Drawer::~Drawer()
{
	for (int i = 0; i < height; i++)
	{
		delete[] z_buff[i];
	}
}

void Drawer::draw_dot(double x, double y, int color, const Poly& p)
{
	int xr = (int)trunc(x) + this->width / 2;
	int yr = -((int)trunc(y) - this->height / 2);
	if (xr >= width || yr >= height || xr < 0 || yr < 0) return;
	double zet = z_buff_get_pix(x, y, p);
	if (zet > z_buff[xr][yr])
	{
		z_buff[xr][yr] = zet;
		putpixel(xr, yr, color);
	}
}

int Drawer::get_dot(double x, double y)
{
	int xr = (int)trunc(x) + this->width / 2;
	int yr = -((int)trunc(y) - this->height / 2);
	return getpixel(xr, yr);
}

void Drawer::draw_line(double x1, double y1, double x2, double y2, int color, const Poly& p)
{
	const double c1 = y2 - y1;
	const double c2 = x2 - x1;
	const double length = sqrt(c1 * c1 + c2 * c2);

	const double xStep = c2 / length;
	const double yStep = c1 / length;

	for (int i = 0; i < length; i++)
	{
		draw_dot(trunc(x1 + xStep * i), trunc(y1 + yStep * i), color, p);
	}
}

double Drawer::z_buff_get_pix(double x, double y, const Poly& p)
{
	double nx = p.get_n().x();
	double ny = p.get_n().y();
	double nz = p.get_n().z();

	double vx = p.get_v().x();
	double vy = p.get_v().y();
	double vz = p.get_v().z();

	double D = -(nx * vx + ny * vy + nz * vz);
	double z = -(nx * x + ny * y + D) / nz;
	return z;
}

void Drawer::fill_z_buff(const Poly& p)
{
	int xr;
	int yr;
	double zet;
	for (int i = -width / 2; i < width / 2; i++)
	{
		for (int j = -height / 2; j < height / 2; j++)
		{
			xr = (int)trunc(i) + this->width / 2;
			yr = -((int)trunc(j) - this->height / 2);
			zet = z_buff_get_pix(i, j, p);
			if (zet > z_buff[xr][yr])
			{
				z_buff[xr][yr] = zet;
			}
		}
	}
}

void Drawer::fill(double x, double y, int color, int bordercolor, const Poly& p)
{
	if (!p.is_onPoly(x, y))
	{
		return;
	}
	int rx = (int)trunc(x) + this->width / 2;
	int ry = -((int)trunc(y) - this->height / 2);
	if (z_buff_get_pix(x, y, p) <= z_buff[rx][ry])
	{
		return;
	}
	struct dot
	{
		int cords[2];
	} nowdot;
	double zet;
	nowdot.cords[0] = (int)trunc(x);
	nowdot.cords[1] = (int)trunc(y);
	stack<dot> dots;
	dot somedot;
	dots.push_back(nowdot);

	while (dots.fast_length() != 0)
	{
		nowdot = dots.pop_back();
		rx = (int)trunc(nowdot.cords[0]) + this->width / 2;
		ry = -((int)trunc(nowdot.cords[1]) - this->height / 2);

		zet = z_buff_get_pix(nowdot.cords[0], nowdot.cords[1], p);
		if (rx >= width || ry >= height || rx < 0 || ry < 0 ||
			zet <= z_buff[rx][ry] || !p.is_onPoly(nowdot.cords[0], nowdot.cords[1])) continue;

		draw_dot(nowdot.cords[0], nowdot.cords[1], color, p);

		// 1 0
		zet = z_buff_get_pix(nowdot.cords[0] + 1, nowdot.cords[1], p);
		if (rx + 1 >= 0 && rx + 1 < width && ry >= 0 && ry < width && zet > z_buff[rx + 1][ry])
		{
			somedot.cords[0] = nowdot.cords[0] + 1;
			somedot.cords[1] = nowdot.cords[1];
			dots.push_back(somedot);
		}

		// 0 1
		zet = z_buff_get_pix(nowdot.cords[0], nowdot.cords[1] + 1, p);
		if (rx >= 0 && rx < width && ry + 1 >= 0 && ry + 1 < width && zet > z_buff[rx][ry - 1])
		{
			somedot.cords[0] = nowdot.cords[0];
			somedot.cords[1] = nowdot.cords[1] + 1;
			dots.push_back(somedot);
		}

		// -1 0
		zet = z_buff_get_pix(nowdot.cords[0] - 1, nowdot.cords[1], p);
		if (rx - 1 >= 0 && rx - 1 < width && ry >= 0 && ry < width && zet > z_buff[rx - 1][ry])
		{
			somedot.cords[0] = nowdot.cords[0] - 1;
			somedot.cords[1] = nowdot.cords[1];
			dots.push_back(somedot);
		}

		// 0 -1
		zet = z_buff_get_pix(nowdot.cords[0], nowdot.cords[1] - 1, p);
		if (rx >= 0 && rx < width && ry - 1 >= 0 && ry - 1 < width && zet > z_buff[rx][ry + 1])
		{
			somedot.cords[0] = nowdot.cords[0];
			somedot.cords[1] = nowdot.cords[1] - 1;
			dots.push_back(somedot);
		}
	}
}

void Drawer::draw_poly(const Poly& p, int color, int colorborders, bool fillflag)
{
	double xmin = (double)(width / 2);
	double ymin = (double)(height / 2);
	double xmax = (double)(-width / 2);
	double ymax = (double)(-height / 2);

	int l = p.get_len();

	for (int j = 0, k = 1; j < l; j++, k = (j + 1) % l)
	{
		draw_line(p.dot(j).x(), p.dot(j).y(), p.dot(k).x(), p.dot(k).y(), colorborders, p);
	}
	if (fillflag)
	{
		for (int i = 0; i < l; i++)
		{
			xmin = min(xmin, p.dot(i).x());
			xmax = max(xmax, p.dot(i).x());
			ymin = min(ymin, p.dot(i).y());
			ymax = max(ymax, p.dot(i).y());
		}
		xmin = max(xmin, -width / 2);
		xmax = min(xmax, width / 2);
		ymin = max(ymin, -height / 2);
		ymax = min(ymax, height / 2);
		for (int i = (int)trunc(xmin); i < (int)trunc(xmax); i += 1)
		{
			for (int j = (int)trunc(ymin); j < (int)trunc(ymax); j += 1)
			{
				fill((double)i, (double)j, color, colorborders, p);
			}
		}
	}
}

void Drawer::clean()
{
	cleardevice();
	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
		{
			z_buff[i][j] = (double)INT_MIN;
		}
}