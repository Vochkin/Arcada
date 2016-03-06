#include "extra.h"
int temp = 0;// condition begin move of circle
int h = 400, w = 400;
double x_r[4], y_r[4], w_r = 70, h_r = 3;
int N = 20; int amount = w / N*(h / N + 1);

vector<cube> v_cube;
circle circ(w / 2, 29);

void init_arrays()
{
	x_r[0] = w / 2 - w_r / 2; y_r[0] = 20;
	x_r[1] = w / 2 - w_r / 2; y_r[1] = h_r + 20;
	x_r[2] = w / 2 + w_r / 2; y_r[2] = h_r + 20;
	x_r[3] = w / 2 + w_r / 2; y_r[3] = 20;

	for (int i = 0, x_ = 0, y_ = h - N;;i++, x_ += N)//create the coords of cube
	{
		if (i == w / N) {
			y_ -= N; x_ = 0; i = 0;
		}
		if (y_ <= h / 2 - N) break;
		cube time(x_, y_);
		v_cube.push_back(time);
		amount += 1;
	}

}

void draw_racket()
{

	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_QUADS);
	glVertex2f(x_r[0], y_r[0]);
	glVertex2f(x_r[1], y_r[1]);
	glVertex2f(x_r[2], y_r[2]);
	glVertex2f(x_r[3], y_r[3]);
	glEnd();
}

void Keyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		if (((((circ.get_x_q(0) > x_r[1] && circ.get_x_q(0) < x_r[2]) || (circ.get_x_q(3) > x_r[1] && circ.get_x_q(3) < x_r[2]))) && (circ.get_y_q(0) == y_r[1])))
				circ.set_direct(-1);
		if (x_r[0] <= 2) break;
		for (int i = 0;i < 4;i++)
			x_r[i] -= 10;
		if (!temp)
		{
			circ.set_x((x_r[0] + x_r[3]) / 2);
			circ.set_y((y_r[1] + 6));
		}
		break;
	case GLUT_KEY_RIGHT:
		if (((((circ.get_x_q(0) > x_r[1] && circ.get_x_q(0) < x_r[2]) || (circ.get_x_q(3) > x_r[1] && circ.get_x_q(3) < x_r[2]))) && (circ.get_y_q(0) == y_r[1])))
			circ.set_direct(1);
		if (x_r[3] >= w-2) break;
		for (int i = 0;i < 4;i++)
		{
			x_r[i] += 10;
		}
		if (!temp)
		{
			circ.set_x((x_r[0] + x_r[3]) / 2);
			circ.set_y((y_r[1] + 6));
		}
		
		break;
	
	}
	
}

void Keyboard2(unsigned char key, int x, int y)
{
	if (key == 32) { 
		temp = 1; 
		glutSetWindowTitle("Good luck");
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	draw_racket();

	for (vector<cube>::iterator i = v_cube.begin();i != v_cube.end();i++)
	{
		i->draw_cube();
	}

	circ.draw_circle();
	glutSwapBuffers();
}

void Timer(int = 0)
{
	display();
	if (temp)
		circ.move_circle(v_cube);
	glutTimerFunc(12, Timer, 0);
}

void Initialize()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char** argv)
{
	init_arrays();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(w, h);
	int hwnd = glutCreateWindow("Press space for start");

	Initialize();

	glutKeyboardFunc(Keyboard2);
	glutSpecialFunc(Keyboard);
	glutDisplayFunc(display);
	glutTimerFunc(10, Timer, 0);

	

	glutMainLoop();

	

	return 0;

}