class star
{
	public:
	
		double x;
		double y;
		void move()
		{
			y--;
		}
		void show()
		{
			glPointSize(1);
			glColor3f(1,1,1);
			glBegin(GL_POINTS);
			glVertex2f(x,y);
			glEnd();
		}
		
	
};
