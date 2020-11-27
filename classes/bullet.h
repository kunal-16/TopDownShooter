class bullet
{
	public:
		double x;
		double y;
		int firing;
		bullet()
		{
			firing=0;
		}
		void getPosition(myship ship)
		{
			x=ship.x;
			y=ship.y+35;
		}
		void fire()
		{

			firing=1;
		}
		void draw()
		{
			glColor3f(1,0,0);
			glLineWidth(3);
			glBegin(GL_LINES);
				glVertex2f(x,y);
				glVertex2f(x,y+10);
			glEnd();
		}
		void move(int offset)
		{
			y=y+offset;
		}
		void reinit()
		{
			firing=0;
		}
};
