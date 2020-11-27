int enemyX[481];
class enemy
{
	public:
	double x;
	double y;

	int alive;
	int explode;
	float r; // Blast Radius;
	enemy()
	{
		alive=1;
		explode=0;
		r=0;
	}
	
	void init()
	{
		x=enemyX[rand()%481];
		y=500;
		alive=1;
		explode=0;
		r=0;
	}

	void draw()
	{
		glColor3f(0.9,0.91,0.98);
		glBegin(GL_POLYGON);
			glVertex2f(x-2,y-20);
			glVertex2f(x-10,y-5);
			glVertex2f(x-2,y+20);
			glVertex2f(x+2,y+20);
			glVertex2f(x+10,y-5);
			glVertex2f(x+2,y-20);
			glVertex2f(x-2,y-20);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex2f(x-10,y-5);
			glVertex2f(x-15,y-5);
			glVertex2f(x-15,y+15);
			glVertex2f(x-5,y+10.625);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex2f(x+10,y-5);
			glVertex2f(x+15,y-5);
			glVertex2f(x+15,y+15);
			glVertex2f(x+5,y+10.625);
		glEnd();
		glColor3f(0,0,0);
		glBegin(GL_LINE_STRIP);
			glVertex2f(x-2,y-20);
			glVertex2f(x-10,y-5);
			glVertex2f(x-2,y+20);
			glVertex2f(x+2,y+20);
			glVertex2f(x+10,y-5);
			glVertex2f(x+2,y-20);
			glVertex2f(x-2,y-20);
		glEnd();
		glBegin(GL_LINE_STRIP);
			glVertex2f(x-10,y-5);
			glVertex2f(x-15,y-5);
			glVertex2f(x-15,y+15);
			glVertex2f(x-5,y+10.625);
		glEnd();
		glBegin(GL_LINE_STRIP);
			glVertex2f(x+10,y-5);
			glVertex2f(x+15,y-5);
			glVertex2f(x+15,y+15);
			glVertex2f(x+5,y+10.625);
		glEnd();
			
	}
	void move(float offset)
	{
		y=y-offset;
	}
	void explosion()
	{
		float i,j,J;
		float asp;
		glColor3f(1,1,0);
		for(i=x-r;i<=x+r;i++)
		{
			asp=r*r-(i-x)*(i-x);
			j=sqrt(asp)+y;
			J=-sqrt(asp)+y;
			glBegin(GL_POINTS);
				glVertex2f(i,j);
				glVertex2f(i,J);
			glEnd();
		}
		r++;
		y--;
	}
};
