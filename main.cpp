#define _USE_MATH_DEFINES

#include "matrixlist.h"
#include "figure.h"
#include <iostream>
#include <sstream>
#define BUFF_DRAWER
#include "drawer.h"

#define MOVEMENT_RATE 5
#define SCALE_RATE 1.05
#define ROTATE_RATE 5
#define SHADOW_COLOR BLACK
#define START_SCALE 100

/*
	mods:
	1. Whole figure:
	2. Par
	3. Pyr
*/

int main(void)
{
	char c;

	Vector3d coordsPar(0, 0, 0), coordsPyr(1 * START_SCALE, 0, 0);
	double scPar = START_SCALE, scPyr = START_SCALE;

	double d_rotxPar = 0, d_rotyPar = 0, d_rotzPar = 0, d_scPar = 1;
	double d_rotxPyr = 0, d_rotyPyr = 0, d_rotzPyr = 0, d_scPyr = 1;

	int parBordersColor, pyrBordersColor;
	char mode = 1;
	Matrix matPar, matPyr, matPyrchange;
	Matrix matshadowParX, matshadowParY, matshadowParZ;
	Matrix matshadowPyrX, matshadowPyrY, matshadowPyrZ;
	Matrix matshadowX, matshadowY, matshadowZ;
	bool fillflag;
	bool changeflag = true;

	Figure originalPar;
	Figure worldPar;
	Figure shadowXPar;
	Figure shadowYPar;
	Figure shadowZPar;

	Figure originalPyr;
	Figure worldPyr;
	Figure shadowXPyr;
	Figure shadowYPyr;
	Figure shadowZPyr;

	Figure walls;
	Matrix matWalls;

	originalPar.add_dot(Vector3d(-1, 1.5, 1)); //0
	originalPar.add_dot(Vector3d(-1, 1.5, -1)); //1
	originalPar.add_dot(Vector3d(1, 1.5, -1)); //2
	originalPar.add_dot(Vector3d(1, 1.5, 1)); //3
	originalPar.add_dot(Vector3d(-1, -1.5, 1)); //4
	originalPar.add_dot(Vector3d(-1, -1.5, -1)); //5
	originalPar.add_dot(Vector3d(1, -1.5, -1)); //6
	originalPar.add_dot(Vector3d(1, -1.5, 1)); //7


	originalPyr.add_dot(Vector3d(-1, -1, 1)); //0
	originalPyr.add_dot(Vector3d(1, -1, 0)); //1
	originalPyr.add_dot(Vector3d(-1, -1, -1)); //2
	originalPyr.add_dot(Vector3d(0, 1, 0)); //3


	originalPar.add_road(0, 1, 2, 3);
	originalPar.add_road(0, 1, 5, 4);
	originalPar.add_road(0, 3, 7, 4);
	originalPar.add_road(1, 2, 6, 5);
	originalPar.add_road(2, 3, 7, 6);
	originalPar.add_road(4, 5, 6, 7);


	originalPyr.add_road(0, 1, 2);
	originalPyr.add_road(0, 1, 3);
	originalPyr.add_road(0, 2, 3);
	originalPyr.add_road(1, 2, 3);

	walls.add_dot(Vector3d(-2, -2, -2)); //0
	walls.add_dot(Vector3d(-2, -2, 15)); //1
	walls.add_dot(Vector3d(-2, 8, -2)); //2
	walls.add_dot(Vector3d(8, -2, -2)); //3
	walls.add_dot(Vector3d(-2, 8, 8)); //4
	walls.add_dot(Vector3d(8, 8, -2)); //5
	walls.add_dot(Vector3d(8, -2, 8)); //6

	walls.add_road(0, 1, 4, 2);
	walls.add_road(0, 1, 6, 3);
	walls.add_road(0, 2, 5, 3);

	Vector3d eye(500, 200, 1000);
	Vector3d target(0, 0, 0);
	Vector3d up(0, 1, 0);
	Vector3d light(800, 1000, 800);
	Vector3d lightX;
	Vector3d lightY;
	Vector3d lightZ;
	Vector3d center;
	Vector3d d_center;
	Vector3d collPar;
	Vector3d collPyr;

	fillflag = false;

	matWalls = getScale(100, 100, 100);
	matWalls = multiply(getLookAt(eye, target, up), matWalls);

	walls.for_allDots(multiplyMatrix, matWalls);

	walls.process_poly();

	Drawer draw(800, 800);

	worldPar = originalPar;
	shadowXPar = originalPar;
	shadowYPar = originalPar;
	shadowZPar = originalPar;

	worldPyr = originalPyr;
	shadowXPyr = originalPyr;
	shadowYPyr = originalPyr;
	shadowZPyr = originalPyr;

	std::ostringstream os;

	os << "Controls:" << std::endl;
	os << "\tw/s - move figure in y axis" << std::endl;
	os << "\ta/d - move figure in x axis" << std::endl;
	os << "\tc/v - move figure in z axis" << std::endl;
	os << "\tq/e - rotate figure around y axis" << std::endl;
	os << "\tz/x - rotate figure around z axis" << std::endl;
	os << "\tr/t - rotate figure around x axis" << std::endl;
	os << "\t-/= - unzoom/zoom figure" << std::endl;
	os << "\tf - on/off render" << std::endl;
	os << "\t1/2/3 - switch mods" << std::endl;
	os << "Mods:" << std::endl;
	os << "\t1 - manipulate the whole figure" << std::endl;
	os << "\t2 - manipulate the parallelepiped" << std::endl;
	os << "\t3 - manipulate the pyromid" << std::endl;
	std::cout << os.str();

	while (1)
	{
		if (kbhit())
		{
			changeflag = true;
			c = getch();
			if (c == 0)
			{
				c = getch();
			}
			while (kbhit()) getch();
			switch (c)
			{
			case 'w':
				switch (mode)
				{
				case 1:
					coordsPar.y() += MOVEMENT_RATE;
					coordsPyr.y() += MOVEMENT_RATE;
					break;
				case 2:
					coordsPar.y() += MOVEMENT_RATE;
					break;
				case 3:
					coordsPyr.y() += MOVEMENT_RATE;
					break;
				}
				break;
			case 's':
				switch (mode)
				{
				case 1:
					coordsPar.y() -= MOVEMENT_RATE;
					coordsPyr.y() -= MOVEMENT_RATE;
					break;
				case 2:
					coordsPar.y() -= MOVEMENT_RATE;
					break;
				case 3:
					coordsPyr.y() -= MOVEMENT_RATE;
					break;
				}
				break;
			case 'a':
				switch (mode)
				{
				case 1:
					coordsPar.x() -= MOVEMENT_RATE;
					coordsPyr.x() -= MOVEMENT_RATE;
					break;
				case 2:
					coordsPar.x() -= MOVEMENT_RATE;
					break;
				case 3:
					coordsPyr.x() -= MOVEMENT_RATE;
					break;
				}
				break;
			case 'd':
				switch (mode)
				{
				case 1:
					coordsPar.x() += MOVEMENT_RATE;
					coordsPyr.x() += MOVEMENT_RATE;
					break;
				case 2:
					coordsPar.x() += MOVEMENT_RATE;
					break;
				case 3:
					coordsPyr.x() += MOVEMENT_RATE;
					break;
				}
				break;
			case 'c':
				switch (mode)
				{
				case 1:
					coordsPar.z() += MOVEMENT_RATE;
					coordsPyr.z() += MOVEMENT_RATE;
					break;
				case 2:
					coordsPar.z() += MOVEMENT_RATE;
					break;
				case 3:
					coordsPyr.z() += MOVEMENT_RATE;
					break;
				}
				break;
			case 'v':
				switch (mode)
				{
				case 1:
					coordsPar.z() -= MOVEMENT_RATE;
					coordsPyr.z() -= MOVEMENT_RATE;
					break;
				case 2:
					coordsPar.z() -= MOVEMENT_RATE;
					break;
				case 3:
					coordsPyr.z() -= MOVEMENT_RATE;
					break;
				}
				break;
			case 'q':
				switch (mode)
				{
				case 1:
					d_rotyPar += ROTATE_RATE;
					d_rotyPyr += ROTATE_RATE;
					break;
				case 2:
					d_rotyPar += ROTATE_RATE;
					break;
				case 3:
					d_rotyPyr += ROTATE_RATE;
					break;
				}
				break;
			case 'e':
				switch (mode)
				{
				case 1:
					d_rotyPar -= ROTATE_RATE;
					d_rotyPyr -= ROTATE_RATE;
					break;
				case 2:
					d_rotyPar -= ROTATE_RATE;
					break;
				case 3:
					d_rotyPyr -= ROTATE_RATE;
					break;
				}
				break;
			case 'r':
				switch (mode)
				{
				case 1:
					d_rotxPar += ROTATE_RATE;
					d_rotxPyr += ROTATE_RATE;
					break;
				case 2:
					d_rotxPar += ROTATE_RATE;
					break;
				case 3:
					d_rotxPyr += ROTATE_RATE;
					break;
				}
				break;
			case 't':
				switch (mode)
				{
				case 1:
					d_rotxPar -= ROTATE_RATE;
					d_rotxPyr -= ROTATE_RATE;
					break;
				case 2:
					d_rotxPar -= ROTATE_RATE;
					break;
				case 3:
					d_rotxPyr -= ROTATE_RATE;
					break;
				}
				break;
			case 'x':
				switch (mode)
				{
				case 1:
					d_rotzPar -= ROTATE_RATE;
					d_rotzPyr -= ROTATE_RATE;
					break;
				case 2:
					d_rotzPar -= ROTATE_RATE;
					break;
				case 3:
					d_rotzPyr -= ROTATE_RATE;
					break;
				}
				break;
			case 'z':
				switch (mode)
				{
				case 1:
					d_rotzPar += ROTATE_RATE;
					d_rotzPyr += ROTATE_RATE;
					break;
				case 2:
					d_rotzPar += ROTATE_RATE;
					break;
				case 3:
					d_rotzPyr += ROTATE_RATE;
					break;
				}
				break;
			case '-':
				switch (mode)
				{
				case 1:
					d_scPar /= SCALE_RATE;
					d_scPyr /= SCALE_RATE;
					break;
				case 2:
					d_scPar /= SCALE_RATE;
					break;
				case 3:
					d_scPyr /= SCALE_RATE;
					break;
				}
				break;
			case '=':
				switch (mode)
				{
				case 1:
					d_scPar *= SCALE_RATE;
					d_scPyr *= SCALE_RATE;
					break;
				case 2:
					d_scPar *= SCALE_RATE;
					break;
				case 3:
					d_scPyr *= SCALE_RATE;
					break;
				}
				break;
			case 'f':
				if (fillflag)
				{
					fillflag = false;
					break;
				}
				fillflag = true;
				break;
			case '1':
				mode = 1;
				break;
			case '2':
				mode = 2;
				break;
			case '3':
				mode = 3;
				break;
			default:
				changeflag = false;
				break;
			}


		}

		if (changeflag)
		{
			scPar *= d_scPar;
			scPyr *= d_scPyr;

			matPar.set_ones();
			matPyr.set_ones();

			matPar = multiply(getRotationX(d_rotxPar), matPar);
			matPar = multiply(getRotationY(d_rotyPar), matPar);
			matPar = multiply(getRotationZ(d_rotzPar), matPar);
			originalPar.for_allDots(multiplyMatrix, matPar);

			matPyr = multiply(getRotationX(d_rotxPyr), matPyr);
			matPyr = multiply(getRotationY(d_rotyPyr), matPyr);
			matPyr = multiply(getRotationZ(d_rotzPyr), matPyr);
			originalPyr.for_allDots(multiplyMatrix, matPyr);

			worldPar.copy_dots(originalPar);
			worldPyr.copy_dots(originalPyr);

			matPar = getScale(scPar, scPar, scPar);

			if (mode == 1)
			{
				matPyrchange = multiply(getScale(d_scPyr, d_scPyr, d_scPyr), matPyr);
				center = substract(coordsPyr, coordsPar);
				d_center = multiplyMatrix(matPyrchange, center);
				d_center = substract(d_center, center);
				coordsPyr = add(coordsPyr, d_center);
			}

			matPyr = getScale(scPyr, scPyr, scPyr);

			matPar = multiply(getTranslation(coordsPar.x(), coordsPar.y(), coordsPar.z()), matPar);
			matPyr = multiply(getTranslation(coordsPyr.x(), coordsPyr.y(), coordsPyr.z()), matPyr);

			if (fillflag)
			{
				shadowXPar.copy_dots(originalPar);
				shadowYPar.copy_dots(originalPar);
				shadowZPar.copy_dots(originalPar);

				shadowXPyr.copy_dots(originalPyr);
				shadowYPyr.copy_dots(originalPyr);
				shadowZPyr.copy_dots(originalPyr);

				matshadowParX = multiply(getTranslation(199.99, 0, 0), matPar);
				matshadowParY = multiply(getTranslation(0, 199.9, 0), matPar);
				matshadowParZ = multiply(getTranslation(0, 0, 199.9), matPar);
				matshadowPyrX = multiply(getTranslation(199.99, 0, 0), matPyr);
				matshadowPyrY = multiply(getTranslation(0, 199.9, 0), matPyr);
				matshadowPyrZ = multiply(getTranslation(0, 0, 199.9), matPyr);

				matshadowY = getTranslation(0, -199.99, 0);
				matshadowY = multiply(getLookAt(eye, target, up), matshadowY);

				matshadowX = getTranslation(-199.99, 0, 0);
				matshadowX = multiply(getLookAt(eye, target, up), matshadowX);

				matshadowZ = getTranslation(0, 0, -199.99);
				matshadowZ = multiply(getLookAt(eye, target, up), matshadowZ);

				lightX = light;
				lightY = light;
				lightZ = light;
				lightX.x() = light.x() + 199.99;
				lightY.y() = light.y() + 199.99;
				lightZ.z() = light.z() + 199.99;
			}

			worldPar.for_allDots(multiplyMatrix, matPar);
			collPar = worldPar.check_collision(Vector3d(-2 * START_SCALE, -2 * START_SCALE, -2 * START_SCALE));
			matPar = getTranslation(-collPar.x(), -collPar.y(), -collPar.z());

			worldPyr.for_allDots(multiplyMatrix, matPyr);
			collPyr = worldPyr.check_collision(Vector3d(-2 * START_SCALE, -2 * START_SCALE, -2 * START_SCALE));
			matPyr = getTranslation(-collPyr.x(), -collPyr.y(), -collPyr.z());

			coordsPar.x() -= collPar.x();
			coordsPar.y() -= collPar.y();
			coordsPar.z() -= collPar.z();

			coordsPyr.x() -= collPyr.x();
			coordsPyr.y() -= collPyr.y();
			coordsPyr.z() -= collPyr.z();

			if (mode == 1)
			{
				coordsPyr.x() -= collPar.x();
				coordsPyr.y() -= collPar.y();
				coordsPyr.z() -= collPar.z();
				matPyr = multiply(getTranslation(-collPar.x(), -collPar.y(), -collPar.z()), matPyr);

				coordsPar.x() -= collPyr.x();
				coordsPar.y() -= collPyr.y();
				coordsPar.z() -= collPyr.z();
				matPar = multiply(getTranslation(-collPyr.x(), -collPyr.y(), -collPyr.z()), matPar);
			}
			matPar = multiply(getLookAt(eye, target, up), matPar);
			worldPar.for_allDots(multiplyMatrix, matPar);

			matPyr = multiply(getLookAt(eye, target, up), matPyr);
			worldPyr.for_allDots(multiplyMatrix, matPyr);

			worldPar.process_poly();
			worldPyr.process_poly();

			if (fillflag)
			{
				matshadowParX = multiply(getTranslation(collPar.x(), collPar.y(), collPar.z()), matshadowParX);
				shadowXPar.for_allDots(multiplyMatrix, matshadowParX);
				shadowXPar.for_allDots(getShadowX, lightX);
				shadowXPar.for_allDots(multiplyMatrix, matshadowX);

				matshadowParY = multiply(getTranslation(collPar.x(), collPar.y(), collPar.z()), matshadowParY);
				shadowYPar.for_allDots(multiplyMatrix, matshadowParY);
				shadowYPar.for_allDots(getShadowY, lightY);
				shadowYPar.for_allDots(multiplyMatrix, matshadowY);

				matshadowParZ = multiply(getTranslation(collPar.x(), collPar.y(), collPar.z()), matshadowParZ);
				shadowZPar.for_allDots(multiplyMatrix, matshadowParZ);
				shadowZPar.for_allDots(getShadowZ, lightZ);
				shadowZPar.for_allDots(multiplyMatrix, matshadowZ);

				matshadowPyrX = multiply(getTranslation(collPyr.x(), collPyr.y(), collPyr.z()), matshadowPyrX);
				shadowXPyr.for_allDots(multiplyMatrix, matshadowPyrX);
				shadowXPyr.for_allDots(getShadowX, lightX);
				shadowXPyr.for_allDots(multiplyMatrix, matshadowX);

				matshadowPyrY = multiply(getTranslation(collPyr.x(), collPyr.y(), collPyr.z()), matshadowPyrY);
				shadowYPyr.for_allDots(multiplyMatrix, matshadowPyrY);
				shadowYPyr.for_allDots(getShadowY, lightY);
				shadowYPyr.for_allDots(multiplyMatrix, matshadowY);

				matshadowPyrZ = multiply(getTranslation(collPyr.x(), collPyr.y(), collPyr.z()), matshadowPyrZ);
				shadowZPyr.for_allDots(multiplyMatrix, matshadowPyrZ);
				shadowZPyr.for_allDots(getShadowZ, lightZ);
				shadowZPyr.for_allDots(multiplyMatrix, matshadowZ);

				shadowXPar.process_poly();
				shadowYPar.process_poly();
				shadowZPar.process_poly();

				shadowXPyr.process_poly();
				shadowYPyr.process_poly();
				shadowZPyr.process_poly();
			}

			draw.clean();

			for (int i = 0, l = walls.length(); i < l; i++)
			{
				draw.draw_poly(walls.get_poly(i), WHITE, BLACK, false);
			}
			for (int i = 0, l = worldPar.length(); i < l; i++)
			{
				parBordersColor = DARKGRAY;
				if (mode == 1 || mode == 2)
				{
					parBordersColor = BLACK;
				}
				if (fillflag)
				{
					parBordersColor = i + 5;
				}
				draw.draw_poly(worldPar.get_poly(i), i + 5, parBordersColor, fillflag);
			}
			for (int i = 0, l = worldPyr.length(); i < l; i++)
			{
				pyrBordersColor = DARKGRAY;
				if (mode == 1 || mode == 3)
				{
					pyrBordersColor = BLACK;
				}
				if (fillflag)
				{
					pyrBordersColor = i + 10;
				}
				draw.draw_poly(worldPyr.get_poly(i), i + 10, pyrBordersColor, fillflag);
			}

			if (fillflag)
			{
				for (int i = 0, l = walls.length(); i < l; i++)
				{
					draw.fill_z_buff(walls.get_poly(i));
				}
				for (int i = 0, l = worldPar.length(); i < l; i++)
				{

					draw.draw_poly(shadowXPar.get_poly(i), SHADOW_COLOR, SHADOW_COLOR, fillflag);
					draw.draw_poly(shadowYPar.get_poly(i), SHADOW_COLOR, SHADOW_COLOR, fillflag);
					draw.draw_poly(shadowZPar.get_poly(i), SHADOW_COLOR, SHADOW_COLOR, fillflag);
				}
				for (int i = 0, l = worldPyr.length(); i < l; i++)
				{
					draw.draw_poly(shadowXPyr.get_poly(i), SHADOW_COLOR, SHADOW_COLOR, fillflag);
					draw.draw_poly(shadowYPyr.get_poly(i), SHADOW_COLOR, SHADOW_COLOR, fillflag);
					draw.draw_poly(shadowZPyr.get_poly(i), SHADOW_COLOR, SHADOW_COLOR, fillflag);
				}

			}

			setcolor(BLACK);
			bgiout << "Mode: ";
			switch (mode)
			{
			case 1:
				bgiout << "Whole figure";
				break;
			case 2:
				bgiout << "Parallelogram";
				break;
			case 3:
				bgiout << "Pyramid";
			}
			outstreamxy(10, 10);

			worldPar.dots_clean();

			shadowYPar.dots_clean();
			shadowXPar.dots_clean();
			shadowZPar.dots_clean();

			worldPyr.dots_clean();

			shadowYPyr.dots_clean();
			shadowXPyr.dots_clean();
			shadowZPyr.dots_clean();

			d_rotxPar = 0;
			d_rotyPar = 0;
			d_rotzPar = 0;

			d_rotxPyr = 0;
			d_rotyPyr = 0;
			d_rotzPyr = 0;

			d_scPar = 1;
			d_scPyr = 1;

#ifdef BUFF_DRAWER
			swapbuffers();
#endif
			changeflag = false;
		}
	}
	return 0;
}