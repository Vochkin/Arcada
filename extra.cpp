#include "extra.h"

void circle::draw_circle()
{
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex2f(x_q[0] = double(x - radius), y_q[0] = double(y - radius));
	glVertex2f(x_q[1] = double(x - radius), y_q[1] = double(y + radius));
	glVertex2f(x_q[2] = double(x + radius), y_q[2] = double(y + radius));
	glVertex2f(x_q[3] = double(x + radius), y_q[3] = double(y - radius));
	glEnd();
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	for (float i = 0.0; i < 2 * 3.14; i += 3.14 / 18)
	{
		glVertex2f(this->x + this->radius*sin(i), this->y + this->radius*cos(i));
	}
	glEnd();
}

void circle::move_circle(vector<cube>& vec)
{
	srand(time(NULL));
	static int t = 1;// if '1', so circle moves to quard, else - to racket
	static int ran = (rand() % 2);
	static int temp = 1;// temp '0' - move to down, if temp '+' - move to up
	static double state_x = x; static double state_y = y;// condition for compare(coords last bump)
	static double y_ = 0; static double x_ = 0;
	
	if (ran+1)
	{
		switch (ran)
		{
			case 0:
				y_ = 2; x_ = -2; ran = -1;break;

			case  1:
				y_ = 2; x_ = 2;t = 0; ran = -1;break;
		}
	}
	
	if (temp == 0)// up or down
	{
		if (((((x_q[0] > x_r[1] && x_q[0] < x_r[2]) || (x_q[3] > x_r[1] && x_q[3] < x_r[2]))) && (y_q[0] < y_r[1]) && (y_q[0] > y_r[0])))// bump into racket
		{
			
			if (x < state_x)
			{
				y_ *= -1;
				if (direction_racket == -1)
				{
					x_ -= 0.3;
					y_ -= 0.2;
				}
				else if (direction_racket == 1) {
					x_ -= 0.4; y_ += 0.3;
				}


			}
			else if (x > state_x)
			{
				y_ *= -1;
				if (direction_racket == -1)
				{
					x_ += 0.4;y_ += 0.3;
				}
				else if (direction_racket == 1) {
					x_ += 0.3; y_ -= 0.2;
				}

			}
			temp = 1;
			state_x = x; state_y = y;
			y += y_;
			x += x_;
			return;
		}
		else
		{
			for (vector<cube>::iterator j = vec.begin();j != vec.end();j++)
			{
				if ((((((x_q[2] + x_q[1]) / 2) >= (*j).get_x(0)) && (((x_q[2] + x_q[1]) / 2) <= (*j).get_x(3))) && ((y_q[2] + y_q[3]) / 2) >= (*j).get_y(3)) && (((y_q[2] + y_q[3]) / 2) <= (*j).get_y(2)))
				{

					vec.erase(j);
					x_ *= -1;break;
					temp = 0;
					state_x = x; state_y = y;
					y += y_;
					x += x_;
					return;
				}
			}
		}
		
		
	}

	if(temp == 1)
	{
		if(y_q[1] >= h)//bump into top
		{
			y_ *= -1;
			temp = 0;
			state_x = x; state_y = y;
		}

		else 
		{
			for (vector<cube>::iterator j = vec.begin();j != vec.end();j++)// bump into quard
			{
				if (((((x_q[2] + x_q[1]) / 2) >= (*j).get_x(0)) && (((x_q[2] + x_q[1]) / 2) <= (*j).get_x(3))) && ((y_q[1] >= (*j).get_y(0)) && (y_q[1] <= (*j).get_y(1))))
					
				{
					vec.erase(j);

					y_ *= -1;

					temp = 0;
					state_x = x; state_y = y;
					y += y_;
					x += x_;
					return;
				}
								
			}
		}
	}
	if (x <= 0 + radius)// bump into left side
	{
		state_x = x; state_y = y;
		x_ *= -1;

	}

	else if (x >= w - radius)// bump into right side
	{
		state_x = x; state_y = y;
		x_ *= -1;
	}

	if (y_q[1] <= 0)//bump into down
		exit(0);
	
	direction_racket = 0;

	y += y_;
	x += x_;

}


