#pragma once

#include <vector>
#include <Windows.h>
#include <gl\glut.h>
#include <math.h>
#include <random>
#include <time.h>

using namespace std;
extern int w, h, N, amount;
extern double x_r[4], y_r[4];

class cube
{
private:
	int x[4]; int y[4];
public:
	cube(int x_0, int y_0)
	{
		x[0] = x_0;
		x[1] = x_0;
		x[2] = x_0 + N;
		x[3] = x_0 + N;

		y[0] = y_0;
		y[1] = y_0 + N;
		y[2] = y_0 + N;
		y[3] = y_0;

	}

	int get_x(int k)
	{
		return x[k];
	}
	int get_y(int k)
	{
		return y[k];
	}
	void draw_cube()
	{
		glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_QUADS);
		glVertex2f(x[0] + 1, y[0] + 1);
		glVertex2f(x[1] + 1, y[1] - 1);
		glVertex2f(x[2] - 1, y[2] - 1);
		glVertex2f(x[3] - 1, y[3] + 1);
		glEnd();

	}
	~cube() {};
};

class circle
{
	double radius = 6;
	int direction_racket = 0;// -1(to left), 1(to right), 0(not move)
	double x; double y;
	double x_q[4]; double y_q[4];
public:

	circle(int x_c, int y_c)
	{
		x = x_c;
		y = y_c;
	}
	void set_direct(int i) { direction_racket = i; }

	int get_x_q(int t) { return x_q[t]; }
	int get_y_q(int t) { return y_q[t]; }

	void set_x(double a) { x = a; }
	void set_y(double b) { y = b; }

	void draw_circle();
	void move_circle(vector<cube>&);

};