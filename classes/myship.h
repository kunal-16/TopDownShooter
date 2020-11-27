class myship
{
	public:
		double x;
		double y;
		int shoot;
		int explode;
		int alive;
		float r; // Blast radius
		myship()
		{
			x=250;
			y=40;
			shoot=0;
			r=0;
			explode=0;
			alive=1;
		}
		void move_left(int offset)
		{
			x=x-offset;
		}
		void move_right(int offset)
		{
			x=x+offset;
		}
		void explosion()
		{
			float i,j,J;
			float asp;
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
			
		}
		void displayShip()
		{

		glColor3f(1,1,1);
			glBegin(GL_LINE_STRIP);
                        glVertex2f(x-5,y-15);
                        glVertex2f(x-15,y-10);
                        glVertex2f(x-20,y-12.5);
                        glVertex2f(x-30,y-5);
                        glVertex2f(x-5,y+15);
                        glVertex2f(x-5,y-15);
                        glEnd();
                glBegin(GL_LINE_STRIP);
                        glVertex2f(x+5,y-15);
                        glVertex2f(x+15,y-10);
                        glVertex2f(x+20,y-12.5);
                        glVertex2f(x+30,y-5);
                        glVertex2f(x+5,y+15);
                        glVertex2f(x+5,y-15);
                        glEnd();
                glBegin(GL_LINE_STRIP);
                        glVertex2f(x-5,y-10);
                        glVertex2f(x,y-12.5);
                        glVertex2f(x+5,y-10);
                        glEnd();
                glBegin(GL_LINE_STRIP);
                        glVertex2f(x-5,y+15);
                        glVertex2f(x-7.5,y+20);
                        glVertex2f(x,y+30);
                        glVertex2f(x+7.5,y+20);
                        glVertex2f(x+5,y+15);
                        glEnd();
                glBegin(GL_LINE_STRIP);
                        glVertex2f(x+5,y+15);
                        glVertex2f(x+5,y-10);
                        glVertex2f(x,y-12.5);
                        glVertex2f(x-5,y-10);
                        glVertex2f(x-5,y+15);
                        glEnd();
              }
         
        void Constructor()
        {
        	x=250;
			y=40;
			shoot=0;
			r=0;
			explode=0;
			alive=1;

        }
};
