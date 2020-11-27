
#include<GL/glut.h>
#include<stdlib.h>
#include<iostream>
#include<math.h> 
#include"classes/gameObjects.h"

#define n 500
  #define instructionScreen 3
 #define startScreen 2
#define game 0
#define over 1
 using namespace std;
extern int enemyX[481];
int WIDTH = 400;
int HEIGHT = 300;
namespace GameObjects
{
	myship ship;
	star s[n];
	bullet b[30];
	int NumberOfBulletsPerFrame;
	enemy e[50];
	special sp;
	char score[]="Score:";
	char health[]="Health:";
	int sco;
	int NumberOfEnemiesPerFrame=4;
	int level;
	float enemyspeed=2;
	int bulletspeed=26;
	int hea=100;
	int gamestate=startScreen;
	int spec=5;	
}

using namespace GameObjects;



void showstars()
{
	int i;
	
	for(i=0;i<n;i++)
	{
		if(s[i].y >= 0)
		{
			s[i].show();
			s[i].move();
		}
		else
		{
			s[i].y=500;
			s[i].x=rand()%500;
		}	
	}
	
}
void FireBulletsIfShot()
{
if(ship.shoot)
	{
		b[NumberOfBulletsPerFrame-1].fire();
		b[NumberOfBulletsPerFrame-1].getPosition(ship);
		ship.shoot=0;
	}
}
void drawship()
{
	
	double x=ship.x;
	double y=ship.y;
	glLineWidth(1);
	glColor3f(1,1,1);
	if(ship.alive)
	{
		 
		ship.displayShip();


	}
	else if(ship.explode)
	{
		ship.explosion();
		if(ship.r == 30)
		{
			gamestate=over;
			glutPostRedisplay();
		}
	}
	FireBulletsIfShot();

	
}
void drawbullet()
{
	int i;

	for(i=0;i<NumberOfBulletsPerFrame;i++)
	{
		if(b[i].firing)
		{
			b[i].draw();
			b[i].move(bulletspeed);
		}
		if(b[i].y > 500)
		{
			b[i].reinit();
			
		}
	}
	if(NumberOfBulletsPerFrame>30)
	{
		NumberOfBulletsPerFrame=0;
	}
}
void drawenemy()
{
	
	int i;
	for(i=0;i<NumberOfEnemiesPerFrame;i++)
	{
		if(e[i].alive)
		{
			e[i].draw();
			e[i].move(enemyspeed);
			if((e[i].y-10) < 0)
			{
				e[i].init();
			}
		}
		if(e[i].explode==1)
		{
			e[i].explosion();
			if(e[i].r == 20)
			{
				e[i].init();
			}
			
		}
	}

	
	
}
void BulletsVsEnemyCollisionTest()
{
	
	int i;
	int j;
	for(i=0;i<NumberOfBulletsPerFrame;i++)
	{
		for(j=0;j<NumberOfEnemiesPerFrame;j++)
		if((e[j].x-10)<=b[i].x && b[i].x <= (e[j].x+10) && e[j].alive)
		{
			if((b[i].y+20)>= (e[j].y-20) && (b[i].y+20) <= (e[j].y+20))
			{
				e[j].alive=0;
				e[j].explode=1;
				b[i].firing=0;
				b[i].x=0;
				b[i].y=0;
				sco +=1;
				level++;
			}
		}
	}
}
void MyShipVsEnemyCollisionTest()
{
	
	int i;
	for(i=0;i<NumberOfEnemiesPerFrame;i++)
	{
		if(e[i].alive)
		{
			if( ( (ship.x-7.5 >= e[i].x-10) && (ship.x-7.5 <= e[i].x+10) && ship.alive ) || ( (ship.x+7.5 >= e[i].x-10) && (ship.x+7.5 <= e[i].x+10) && ship.alive ) )
			{
				if(((ship.y+15 >= e[i].y-20) && (ship.y+15 <= e[i].y+20) )|| ((ship.y+30 >= e[i].y-20) && (ship.y+30 <= e[i].y+20)))
				{
					hea=hea-5;
					if(hea < 0) {hea=0;ship.alive =0;ship.explode=1;} 
					e[i].alive=0;
					e[i].explode=1;
				}
			}
			if( ( (ship.x-30 >= e[i].x-10) && (ship.x-30 <= e[i].x+10) && ship.alive ) || ( (ship.x+30 >= e[i].x-10) && (ship.x+30 <= e[i].x+10) ) && ship.alive )
			{
				if(((ship.y-15 >= e[i].y-20) && (ship.y-15 <= e[i].y+20) )|| ((ship.y+15 >= e[i].y-20) && (ship.y+15 <= e[i].y+20)))
				{
					hea=hea-2;
					if(hea< 0) {hea=0;ship.alive=0;ship.explode=1;}
					e[i].alive=0;
					e[i].explode=1;
				}
			}
		}
	}
	
}

void SpecialWeaponVsEnemyCollisionTest()
{
	int i;
	if(sp.firing)
	for(i=0;i<NumberOfEnemiesPerFrame;i++)
	{
		if(sp.y >= e[i].y-20 && sp.y <= e[i].y+20 && e[i].alive)
		{
			e[i].alive=0;
			e[i].explode=1;
			sco++;
			level++;
		}
	}
}

void displayText()
{
	char spe[]="Special:";
	int temp=sco;
	char ch[3]={'0','0','0'};
	char c;
	int rem;
	glColor3f(0,0,1);
	glRasterPos2f(400,470);
	int i;
	for(i=0;i<sizeof(score);i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,score[i]);
	i=2;
	do
	{
		rem=temp%10;
		temp=temp/10;
		c='0'+rem;
		ch[i]=c;
		i--;
	}while(temp);
	for(i=0;i<sizeof(ch);i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,ch[i]);

 	for(i=0;i<3;i++)
 	{
 		ch[i]='0';
 	}

	 glRasterPos2f(0,470);

        for(i=0;i<sizeof(health);i++)
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,health[i]);

        temp=hea;

        i=2;
        do
        {
                rem=temp%10;
                temp=temp/10;
                c='0'+rem;
                ch[i]=c;
                i--;
        }while(temp);
        for(i=0;i<sizeof(ch);i++)
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,ch[i]);

        glRasterPos2f(0,450);
        for(i=0;i<sizeof(spe);i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,spe[i]);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,c='0'+spec);

}

void drawspecial()
{
	if(sp.shoot)
	{
		sp.firing=1;
		sp.getPosition(ship);
		sp.shoot=0;
	}
	if(sp.firing)
	{
		sp.move();
		if(sp.y > 500)
		{
			sp.firing=0;
			sp.y=-10;
		}
	}
}


void gamedisplay()
{
	if(level >= 10)
	{
		enemyspeed +=0.5;
		level=0;
		if(NumberOfEnemiesPerFrame <= 7) NumberOfEnemiesPerFrame++;
	}
	
	// glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	showstars();
	
	drawship();
	drawenemy();
	drawbullet();
	drawspecial();
	BulletsVsEnemyCollisionTest();
	MyShipVsEnemyCollisionTest();
	SpecialWeaponVsEnemyCollisionTest();
	displayText();
	glFlush();
	system("sleep 0.00001");
	glutSwapBuffers();
	glutPostRedisplay();	
}
void move(int x, int y)
{
	ship.x=x;
	glutPostRedisplay();
}
void reshape(int w, int h)
{
	HEIGHT=h;
	WIDTH=w;
	glViewport(0,0,w,h);
	double asp=(float)w/(float)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
		glOrtho(0,500,0,500,-10,10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutPostRedisplay();
	
}
void Reinitialization()
{
	gamestate=game;
	ship.Constructor();

	enemyspeed=2;
	hea=100;
	spec=5;
	sco=0;
	int i;
	for(i=0;i<NumberOfEnemiesPerFrame;i++)
	{
		e[i].init();
	}
	NumberOfEnemiesPerFrame=4;

}
void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'Z':
		case 'z':	if(ship.alive)
					{ship.shoot=1;
				NumberOfBulletsPerFrame++;}
			break;
		case 'X':
		case 'x': if(ship.alive && !sp.firing && spec > 0)
			{
			sp.shoot=1;
			spec--;
		case 'R':
		case 'r': if(gamestate == over)
			{
					Reinitialization();
			}
		case '1': if(gamestate == startScreen){ gamestate=game; glutPostRedisplay();}
			break;
		case '2': if(gamestate == startScreen){gamestate=instructionScreen;glutPostRedisplay();}
		break;
		case 'b': if(gamestate == instructionScreen){ gamestate=startScreen;glutPostRedisplay();}
		}
			
		break;
			
	}
	glutPostRedisplay();
}
void overdisplay()
{
	char text1[]="GAME OVER";
	char text2[]="You Scored ";
	char text3[]="Press \'r\' to restart";
	char ch[]={'0','0','0'};
	char c;
	int rem;
	int temp=sco;
	
	glColor3f(1,0,0);
	glRasterPos2f(180,250);
	int i;
	for(i=0;i<sizeof(text1);i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,text1[i]);
	glRasterPos2f(180,150);
	for(i=0;i<sizeof(text2);i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,text2[i]);
	i=2;
	do
	{
		rem=temp%10;
		temp=temp/10;
		c='0'+rem;
		ch[i]=c;
		i--;
	}while(temp);
	for(i=0;i<sizeof(ch);i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,ch[i]);
	glRasterPos2f(180,130);
	
	for(i=0;i<sizeof(text3);i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,text3[i]);

	 glFlush();
	 glutSwapBuffers();
}
void startScreenDisplay()
{
	char text0[]="STAR RAGE\n";
	char text3[]="How long can you survive ?\n";
	char text1[]="Press 1 to play\n";
	char text2[]="Press 2 for instructions\n";
	char dev[]="Developed by\n";
	char name1[]="Luckyson Khaidem : 1PE12CS080\n";
	char name2[]="Nishant Niket: 1PE12CS107\n";
	glColor3f(1,1,1);
	glRasterPos2f(170,250);
	int i;
	for(i=0;i<sizeof(text1);i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,text1[i]);
	glRasterPos2f(170,220);
	for(i=0;i<sizeof(text2);i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,text2[i]);
	glRasterPos2f(170,400);
	for(i=0;i<sizeof(text0);i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,text0[i]);
	// glRasterPos2f(170,350);
	// for(i=0;i<sizeof(text3);i++)
	// 	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,text3[i]);
	glColor3f(1,0,0);
	glRasterPos2f(10,120);
		for(i=0;i<sizeof(dev);i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10,dev[i]);
	glRasterPos2f(10,100);
		for(i=0;i<sizeof(name1);i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10,name1[i]);
	glRasterPos2f(10,80);
		for(i=0;i<sizeof(name2);i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10,name2[i]);

	glFlush();
	glutSwapBuffers();
}
void displayInstructions()
{
	char text[][100]={"Earth is attacked by Invading Aliens.","Your job is to defend your planet","Move with the mouse","Movement is restricted only to the X-axis", "Press \'z\' to shoot","Press \'x\' to use special weapon","Press \'b\' to go back to main menu"};
	glColor3f(1,1,1);
	int i,j, height=450;
	glColor3f(1,1,1);
	for(i=0;i<7;i++)
	{
		glRasterPos2f(50,height);
		for(j=0;j<sizeof(text[i]);j++)
		{
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,text[i][j]);
		}
		height=height-50;
	}
		glFlush();
		glutSwapBuffers();


}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	switch(gamestate)
	{
		case game: gamedisplay();
		break;
		case over: overdisplay();
		break;
		case startScreen: startScreenDisplay();
		break;
		case instructionScreen: displayInstructions();
		break;
	}
	
	
}
void myinit()
{	
	int i;
	int inc=10;
	glClearColor(0,0,0,0);
	for(i=0;i<n;i++)
	{
		s[i].x=rand()%500;
		s[i].y=rand()%500;
		
	}
	for(i=0;i<481;i++)
	{
		enemyX[i]=inc;
		inc++;
	}
}


int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(500,500);
	glutCreateWindow("Star Rage");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutPassiveMotionFunc(move);
	glutKeyboardFunc(keyboard);
	glutSetCursor(GLUT_CURSOR_NONE);
	glEnable(GL_TEXTURE_2D);
	myinit();
	glutMainLoop();
}


