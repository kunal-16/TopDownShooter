GLfloat colors[][3]={{1,0,0},{1,1,1},{0,1,0},{0,0,1}};
class special
{
	public:
	float y;
	int firing;
	int shoot;
	
	int curcolor;
	special()
	{
			curcolor=0;
	}
	void getPosition(myship ship)
	{
		y=ship.y+30;
	}
	void move()
	{
		glColor3fv(colors[curcolor]);
		glBegin(GL_LINES);
			glVertex2f(0,y);
			glVertex2f(500,y);
			glEnd();
		curcolor=(curcolor+1)%4;
		y=y+2;
	}
};

