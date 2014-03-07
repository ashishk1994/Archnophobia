#include <iostream>
#include<cstdio>
#include <cmath>
#include <vector>
#include<deque>
#include <GL/glut.h>
#include<algorithm>
#include<sstream>
#include<iomanip>
using namespace std;

#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)

// Function Declarations
void drawScene();
void update(int value);
void func(int value);
void generate(int value);
void ball_update(int value);
void drawBox(float len);
void drawBall(float rad);
void drawGluCylinder(float,float,float,float);
void drawTriangle();
void drawRect(float,float);
void drawRectCG(float,float);
void drawRectCR(float,float);
void drawRectCG2(float,float);
void drawRectCR2(float,float);
void drawRect1(float,float);
void drawCan(float,float);
void drawUCan(float,float);
void drawRCan(float,float);
void drawLCan(float,float);
void drawline(int,int);
void drawsline1(float,float,float,int);
void drawsline2(float,float,float,int);
void drawsline3(float,float,float,int);
void drawsline4(float,float,float,int);
void drawsline5(float,float,float,int);
void drawsline6(float,float,float,int);
void drawsline11(float,float,float,int);
void drawsline21(float,float,float,int);
void drawsline31(float,float,float,int);
void drawsline41(float,float,float,int);
void drawsline51(float,float,float,int);
void drawsline61(float,float,float,int);
void mousepos(int,int);
void motionhandler(int,int);
void drawl(int);
void lvl(int);
void drawlinecan();
void initRendering();
void handleResize(int w, int h);
void handleKeypress1(unsigned char key, int x, int y);
void handleKeypress2(int key, int x, int y);
void handlegreen(int key, int x, int y);
void handlered(int key, int x, int y);
void handleblue(int key, int x, int y);
void handlegoli(int key, int x, int y);
void handleMouseclick(int button, int state, int x, int y);

// Global Variables
float ball_x = 0.0f;
float ball_velx = 0.00f;
float ball_vely = -0.02f;
float box_len = 4.0f;
float ball_y = (box_len/2);
float ball_rad = (0.2*box_len*(sin(DEG2RAD(45)))+box_len*0.04)/2;
float tri_x = 0.0f;
float tri_y = -(box_len/2)+(0.1*box_len)/2;
float theta = 0.0f; 
float rect_len=0.90f;
float green_rad=(box_len/8);
float green_x=-(box_len/2)+(green_rad/2);
float green_y=-(box_len/2)+(box_len/12);
float green_height=(box_len/6);
float red_rad=(box_len/8);
float red_x=(box_len/2)-(red_rad)/2;
float red_y=-(box_len/2)+(box_len/12);
float red_height=(box_len/6);
float line_vely=10.0f;
float line_x=10.01f;
float line_y=0.02f;
float gll=-(box_len/2)+green_rad/2;
float glr=red_x;
float rll=gll;
float rlr=red_x;
float bll=(-box_len/2+box_len*0.1);
float blr=(box_len/2-box_len*0.1);
float mouseposx;
float mouseposy;
float mouseposz;

float check=0;
int cnt=0;
int t=1;
int pase=0;
int green=0;
int red=0;
int fgreen=0;
int fred=0;
int fblue=0;
int fp=0;
int over=0;
int mode=0;
int side=0;
int kano=0;
int level=0;
int tot=0;

typedef struct ball{
	float x;
	float y;
	float velx;
	float vely;
	float rad;
	int flag;
	int count;
}ball;

typedef struct las{
	float x;
	float y;
	float vel;
	float col;
	float theta;
}las;

vector<ball> balls;
vector<las> laser;
vector<las> remain;
int main(int argc, char **argv) {


	//initialize line array of 20;
	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	int w = glutGet(GLUT_SCREEN_WIDTH);
	int h = glutGet(GLUT_SCREEN_HEIGHT);
	int windowWidth = w * 2 / 3;
	int windowHeight = h * 2 / 3;

	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition((w - windowWidth) / 2, (h - windowHeight) / 2);

	glutCreateWindow("CSE251_sampleCode");  // Setup the window
	initRendering();

	// Register callbacks
	glutDisplayFunc(drawScene);
	glutIdleFunc(drawScene);
	glutKeyboardFunc(handleKeypress1);
	glutReshapeFunc(handleResize);
	if(pase==0 && over==0)
	{
		glutMouseFunc(handleMouseclick);
		glutMotionFunc(motionhandler);
		glutTimerFunc(10, update, 0);	
		glutTimerFunc(1000,generate, 0);
		glutTimerFunc(1000,lvl, 0);
		glutTimerFunc(12,ball_update, 0);
		//	glutTimerFunc(1000,func, 0);
	}
	glutMainLoop();
	return 0;
}

float RandomFloat(float a, float b) {
	float random = ((float) rand()) / (float) RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}
// Function to draw objects on the screen
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Draw Box
	if(over==0)
	{

		glPushMatrix();
		// Draw Box
		glTranslatef(0.0f, 0.0f, -5.0f);
		glColor3f(0.0f, 1.0f, 1.0f);
		drawBox(box_len);

		// Draw Box
		glPushMatrix();
		glTranslatef(-0.0f,-(box_len/2),0.0f);
		glColor3f(0.60f,0.179f,0.113f);
		//glRotatef(-100.0f,1.0f,0.0f,0.0f);
		drawRect1(box_len,0.1*box_len);
		glPopMatrix();
		
	

		// Draw Ball
		int i;
		for(i=0;i<balls.size();i++)
		{
			glPushMatrix();
			glTranslatef(balls[i].x,balls[i].y, 0.0f);
			if(balls[i].flag==0)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
			}
			else if(balls[i].flag==1)
			{
				glColor3f(0.0f, 1.0f, 0.0f);
			}
			else
			{
				glColor3f(0.0f, 0.0f, 0.0f);
			}
			drawBox(ball_rad/4);
			glPopMatrix();

			glPushMatrix();
			drawsline1(balls[i].x,balls[i].y,0.02*box_len,balls[i].flag);
			glPopMatrix();	

			glPushMatrix();
			drawsline2(balls[i].x,balls[i].y,0.02*box_len,balls[i].flag);
			glPopMatrix();	

			glPushMatrix();
			drawsline3(balls[i].x,balls[i].y,0.02*box_len,balls[i].flag);
			glPopMatrix();	

			glPushMatrix();
			drawsline4(balls[i].x,balls[i].y,0.02*box_len,balls[i].flag);
			glPopMatrix();	

			glPushMatrix();
			drawsline5(balls[i].x,balls[i].y,0.02*box_len,balls[i].flag);
			glPopMatrix();	

			glPushMatrix();
			drawsline6(balls[i].x,balls[i].y,0.02*box_len,balls[i].flag);
			glPopMatrix();	

			glPushMatrix();
			drawsline11(balls[i].x,balls[i].y,0.02*box_len,balls[i].flag);
			glPopMatrix();	

			glPushMatrix();
			drawsline21(balls[i].x,balls[i].y,0.02*box_len,balls[i].flag);
			glPopMatrix();	

			glPushMatrix();
			drawsline31(balls[i].x,balls[i].y,0.02*box_len,balls[i].flag);
			glPopMatrix();	

			glPushMatrix();
			drawsline41(balls[i].x,balls[i].y,0.02*box_len,balls[i].flag);
			glPopMatrix();	

			glPushMatrix();
			drawsline51(balls[i].x,balls[i].y,0.02*box_len,balls[i].flag);
			glPopMatrix();	

			glPushMatrix();
			drawsline61(balls[i].x,balls[i].y,0.02*box_len,balls[i].flag);
			glPopMatrix();	




		}

		//Draw Cylinder Green
		if(fgreen==0)
		{
			glPushMatrix();
			glTranslatef(green_x,green_y, 0.0f);
			glColor3f(0.5f, 1.0f, 0.5f);
			drawRectCG(green_rad,green_height/2);
			glPopMatrix();
		

			glPushMatrix();
			glTranslatef(green_x,green_y-green_height/2,0.0f);
			glColor3f(0.0f,(153.0/255),0.0f);
			glRotatef(-100.0f,1.0f,0.0f,0.0f);
			drawBall(green_rad/2);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(green_x,green_y+green_height/2,0.0f);
			glColor3f(0.0f,(153.0/255),0.0f);
			glRotatef(-93.0f,1.0f,0.0f,0.0f);
			drawBall(green_rad/2);
			glPopMatrix();
			
		
		}
		else
		{
			glPushMatrix();
			glTranslatef(green_x,green_y, 0.0f);
			glColor3f(0.2f, 1.0f, 0.2f);
			//glScalef(0.5f,0.5f,0.5f);
			//glRotatef(-90.0f,1.0f,0.0f,0.0f);
			//drawGluCylinder(green_height,green_rad,35,36);
			drawRectCG2(green_rad,green_height/2);
			glPopMatrix();
		

			glPushMatrix();
			glTranslatef(green_x,green_y-green_height/2,0.0f);
			glColor3f(0.0f,(153.0/255),0.0f);
			glRotatef(-100.0f,1.0f,0.0f,0.0f);
			drawBall(green_rad/2);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(green_x,green_y+green_height/2,0.0f);
			glColor3f(0.0f,(153.0/255),0.0f);
			glRotatef(-93.0f,1.0f,0.0f,0.0f);
			drawBall(green_rad/2);
			glPopMatrix();


		}

		if(fred==0)
		{
			glPushMatrix();
			glTranslatef(red_x,red_y, 0.0f);
			glColor3f(1.0f, 0.5f, 0.5f);
			//glScalef(0.5f,0.5f,0.5f);
			//glRotatef(-90.0f,1.0f,0.0f,0.0f);
			//drawGluCylinder(green_height,green_rad,35,36);
			drawRectCR(red_rad,red_height/2);
			glPopMatrix();
		

			glPushMatrix();
			glTranslatef(red_x,red_y-red_height/2,0.0f);
			glColor3f((153.0/255), 0.0f, 0.0f);
			glRotatef(-100.0f,1.0f,0.0f,0.0f);
			drawBall(red_rad/2);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(red_x,red_y+red_height/2,0.0f);
			glColor3f((153.0)/255, 0.0f, 0.0f);
			glRotatef(-93.0f,1.0f,0.0f,0.0f);
			drawBall(red_rad/2);
			glPopMatrix();
			
		}
		else
		{
			glPushMatrix();
			glTranslatef(red_x,red_y, 0.0f);
			glColor3f(1.0f, 0.2f, 0.2f);
			drawRectCR2(red_rad,red_height/2);
			glPopMatrix();
		

			glPushMatrix();
			glTranslatef(red_x,red_y-red_height/2,0.0f);
			glColor3f((153.0/255), 0.0f, 0.0f);
			glRotatef(-100.0f,1.0f,0.0f,0.0f);
			drawBall(red_rad/2);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(red_x,red_y+red_height/2,0.0f);
			glColor3f((153.0/255), 0.0f, 0.0f);
			glRotatef(-93.0f,1.0f,0.0f,0.0f);
			drawBall(red_rad/2);
			glPopMatrix();
		}
		//Draw Rectangle
		for(i=0;i<laser.size();i++)
		{
			glPushMatrix();
			drawline(i,laser[i].col);
			glPopMatrix();
		}
		for(i=0;i<remain.size();i++)
		{
			glPushMatrix();
			drawl(i);
			glPopMatrix();
		}
		glPushMatrix();
		glTranslatef(tri_x,tri_y,0.0f);
		if(fblue)
		{
			glColor3f(0.25f,0.25f, 1.0f);
		}
		else
		{
			glColor3f(0.5f,0.5f, 1.0f);
		}
		glRotatef(theta,0.0f,0.0f,1.0f);
		drawCan((box_len/2+box_len/8)*0.1,0.06*box_len);
		glPopMatrix();


		glPushMatrix();
		glTranslatef(tri_x,tri_y,0.0f);
		if(fblue)
		{
			glColor3f(0.25f,0.25f, 1.0f);
		}
		else
		{
			glColor3f(0.5f,0.5f, 1.0f);
		}
		glRotatef(theta,0.0f,0.0f,1.0f);
		drawUCan(0.1f,(0.1f)+(0.06*box_len));
		glPopMatrix();

		glPushMatrix();
		glTranslatef(tri_x,tri_y,-0.0f);
		if(fblue)
		{
			glColor3f(0.25f,0.25f, 1.0f);
		}
		else
		{
			glColor3f(0.5f,0.5f, 1.0f);
		}

		glRotatef(theta,0.0f,0.0f,1.0f);
		drawRCan(0.57,0.06*box_len);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(tri_x,tri_y,-0.0f);
		if(fblue)
		{
			glColor3f(0.25f,0.25f, 1.0f);
		}
		else
		{
			glColor3f(0.5f,0.5f, 1.0f);
		}

		glRotatef(theta,0.0f,0.0f,1.0f);
		drawLCan(0.07,0.06*box_len);
		glPopMatrix();


		glPushMatrix();
		drawlinecan();
		glPopMatrix();

		//drawBase
		glPopMatrix();
		glEnd();

		glPushMatrix();
		glTranslatef(0.0f,(box_len/2+(0.03*box_len)), -5.0f);
		glColor3f(0.0f, 1.0f, 1.0f);
		drawRect(box_len,0.03*box_len);
		glPopMatrix();

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0.0,4, 0.0,4);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glColor3f(1.0f, 0.0f, 0.0f);//needs to be called before RasterPos
		glRasterPos3f((box_len/2+box_len/8),(box_len-box_len/6),0.0);
		ostringstream convert1;
		convert1 << level;
		string res1=convert1.str();
		std::string s1 = "Level "+res1;
		for (std::string::iterator i = s1.begin(); i != s1.end(); ++i)
		{
			char c = *i;
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,c);
		}
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();


		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0.0,4, 0.0,4);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glColor3f(1.0f, 0.0f, 0.0f);//needs to be called before RasterPos
		glRasterPos3f((box_len/2+box_len/8),(box_len-box_len/8),0.0);
		ostringstream convert;
		convert << cnt;
		string res=convert.str();
		std::string s = "Score :  "+res;
		for (std::string::iterator i = s.begin(); i != s.end(); ++i)
		{
			char c = *i;
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,c);
		}
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();

	}
	else
	{

		glPushMatrix();
		// Draw Box
		glTranslatef(0.0f, 0.0f, 0.0f);
		glColor3f(0.0f, 1.0f, 1.0f);
		drawBox(box_len);

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0.0,4, 0.0,4);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glColor3f(1.0f, 0.0f, 0.0f);//needs to be called before RasterPos
		glRasterPos2f(2.0,2.5);
		std::string s = "Game Over";
		void * font = GLUT_BITMAP_9_BY_15;

		for (std::string::iterator i = s.begin(); i != s.end(); ++i)
		{
			char c = *i;
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,c);
		}
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		glPushMatrix();
		glLoadIdentity();
		glColor3f(1.0f, 0.0f, 0.0f);//needs to be called before RasterPos
		glRasterPos2f(2.0,1.8);
		ostringstream convert;
		convert << cnt;
		string res=convert.str();
		std::string s1 = "Your Score is:"+res;

		for (std::string::iterator i = s1.begin(); i != s1.end(); ++i)
		{
			char c = *i;
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
		}
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();

		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glEnable(GL_TEXTURE_2D);
		glPopMatrix();


		glutTimerFunc(4000,func, 0);

	}

	glPushMatrix();
	glTranslatef(-(box_len/2+0.2*box_len), 0.0f, -5.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	drawRect(0.2*box_len*2,box_len);
	glPopMatrix();
	glPushMatrix();
	// Draw Box
	glTranslatef((box_len/2+0.2*box_len), 0.0f, -5.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	drawRect(0.2*box_len*2,box_len);
	glPopMatrix();

	glutSwapBuffers();
	glutPostRedisplay();
}

//return the value of mouse position
void mousepos(int x, int y)
{
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;

	glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
	glGetDoublev( GL_PROJECTION_MATRIX, projection );
	glGetIntegerv( GL_VIEWPORT, viewport );

	winX = (float)x;
	winY = (float)viewport[3] - (float)y;
	glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

	gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

	mouseposx=posX*100/2;
	mouseposy=(posY*100)/2;
	mouseposz=posZ*100;
}

//function that gives distance between two points
float dist(float x1,float y1,float x2,float y2)
{
	return (sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)));
}

void lvl(int value)
{
	level++;
	glutTimerFunc(60000,lvl, 0);
}


// Function to handle all calculations in the scene
void update(int value) {

	if(over==0)
	{
		kano++;
		if(kano>50)
		{
			kano=50;
		}
		//update position of line 
		int i,rm,j;
		for(i=0;i<laser.size();i++)
		{ 
			float x1=laser[i].x+0.4*sin(DEG2RAD(-1*laser[i].theta));
			float y1=laser[i].y+0.4*cos(DEG2RAD(-1*laser[i].theta));
			if(laser[i].y>(box_len/2))
			{
				laser.erase(laser.begin()+i);
				remain.erase(remain.begin()+i);
			}
			//left wiall
			else if(x1<-(box_len/2) )//&& laser[i].col==0)
			{
				remain[i].theta=laser[i].theta;
				remain[i].x=laser[i].x;
				remain[i].y=laser[i].y;
				laser[i].theta=-1*laser[i].theta;
				laser[i].x=(laser[i].x-0.4*sin(DEG2RAD(remain[i].theta))+0.4*sin(DEG2RAD(-1*remain[i].theta)));
				laser[i].col=1;
				remain[i].vel=laser[i].vel;
			}
			else if(x1>(box_len/2))//&& laser[i].col==0)
			{
				remain[i].theta=laser[i].theta;
				remain[i].x=laser[i].x;
				remain[i].y=laser[i].y;
				laser[i].theta=-1*laser[i].theta;
				laser[i].col=1;
				laser[i].x=(laser[i].x-0.4*sin(DEG2RAD(remain[i].theta))+0.4*sin(DEG2RAD(-1*remain[i].theta)));
				remain[i].vel=laser[i].vel;

			}
			laser[i].y+=(laser[i].vel*cos(DEG2RAD(-1*laser[i].theta)));
			laser[i].x+=(laser[i].vel*sin(DEG2RAD(-1*laser[i].theta)));
			remain[i].y+=(remain[i].vel*cos(DEG2RAD(-1*remain[i].theta)));
			remain[i].x+=(remain[i].vel*sin(DEG2RAD(-1*remain[i].theta)));
			int fl=0;
			for(j=0;j<balls.size();j++)
			{
				if((y1<=(balls[j].y+ball_rad/2))&&(y1>=(balls[j].y-ball_rad/2))&&(x1>=(balls[j].x-ball_rad/2))&&(x1<=(balls[j].x+ball_rad/2)))
				{
					if(balls[j].flag==2)
					{
						cnt++;
					}
					balls.erase(balls.begin()+j);
					laser.erase(laser.begin()+i);
					remain.erase(remain.begin()+i);
					fl=1;
					break;
				}
			}
		}
		int k;
		for(j=0;j<balls.size();j++)
		{
			if(dist(balls[j].x,balls[j].y,green_x,green_y)<=fabs(green_height/2+ball_rad/2) && (balls[j].y>=green_y+green_height/2) )//&& fgreen==1)
			{
				if(balls[j].flag==1)
				{
					green++;
					cnt++;
				}
				else
				{
					cnt--;
					green--;
				}
				cout<<"Your Score Is :"<<cnt<<endl;
				balls.erase(balls.begin()+j);
			}
			if(dist(balls[j].x,balls[j].y,red_x,red_y)<=fabs(red_height/2+ball_rad/2) && (balls[j].y>=red_y+red_height/2))//&& fred==1)
			{
				if(balls[j].flag==0)
				{
					red++;
					cnt++;
				}
				else
				{
					cnt--;
					red--;
				}
				balls.erase(balls.begin()+j);
			}
			if(balls[j].x>=(tri_x-(0.1*box_len/2)) && balls[j].x <=(tri_x+0.1*box_len/2) && balls[j].y-ball_rad/2<=(tri_y+0.1*box_len/2) && balls[j].vely!=0)
			{
				over=1;
				system("aplay gameover.wav &");
				cout<<"Your Score Is:"<<cnt<<endl;
			}
			else if(balls[j].y<=-(box_len/2-0.1*box_len/4))
			{
				if(glr>balls[j].x && balls[j].x>green_x)
				{
					glr=balls[j].x-ball_rad/2;	
				}
				if(gll<balls[j].x && balls[j].x<green_x)
				{
					gll=balls[j].x+ball_rad/2;
				}

				if(rlr>balls[j].x && balls[j].x>red_x)
				{
					rlr=balls[j].x-ball_rad/2;	
				}
				if(rll<balls[j].x && balls[j].x<red_x)
				{
					rll=balls[j].x+ball_rad/2;
				}


				if(blr>balls[j].x && balls[j].x>tri_x)
				{
					blr=balls[j].x-ball_rad/2;	
				}
				if(bll<balls[j].x && balls[j].x<tri_x)
				{
					bll=balls[j].x+ball_rad/2;
				}

				if(balls[j].count==0)
				{
					system("aplay collision.wav &");
					balls[j].count=1;
					cnt-=5;
				}
				balls[j].vely=0.0f;
			}
		}
		if(pase==0)
		{
			glutTimerFunc(10, update, 0);
		}
	}
}

void ball_update(int value)
{
	int i;
	for(i=0;i<balls.size();i++)
	{
		balls[i].y += balls[i].vely;
	}
	if(pase==0)
	{
		glutTimerFunc(12, ball_update, 0);
	}
}

void func(int value)
{
	exit(0);
}

void generate(int value)
{	
	int i;
	float rnd=RandomFloat(-(box_len/2-ball_rad/2),(box_len/2-ball_rad/2));
	float rnd1;
	rnd1=RandomFloat(0.001,0.015*level);
	ball bal;
	bal.x=rnd;
	bal.y=ball_y;
	bal.velx=0.0f;
	bal.vely=-rnd1;
	bal.rad=0.0f;
	bal.count=0;
	bal.flag=rand()%3;
	balls.push_back(bal);
	if(pase==0)
	{
		glutTimerFunc(2000,generate, 0);
	}
}

void drawsline1(float x,float y,float length,int fl)
{
	glLineWidth(2.5); 
	glTranslatef(x,y,-0.0f);
	if(fl==0)
	{
		glColor3f(1.0f, 0.0f, 0.0f);
	}
	else if(fl==1)
	{
		glColor3f(0.0f, 1.0f, 0.0f);
	}
	else
	{
		glColor3f(0.0f, 0.0f, 0.0f);
	}
	glBegin(GL_LINES); 
	glVertex3f(length*(sin(DEG2RAD(45))),-length*(sin(DEG2RAD(45))),0.0f); 
	glVertex3f(-length*(sin(DEG2RAD(45))),length*(sin(DEG2RAD(45))),0.0f); 
	glEnd(); 
}

void drawsline3(float x,float y,float length,int fl)
{
	glLineWidth(2.5); 
	glTranslatef(x,y,-0.0f);
	if(fl==0)
	{
		glColor3f(1.0f, 0.0f, 0.0f);
	}
	else if(fl==1)
	{
		glColor3f(0.0f, 1.0f, 0.0f);
	}
	else
	{
		glColor3f(0.0f, 0.0f, 0.0f);
	}
	glBegin(GL_LINES); 
	glVertex3f(0.02*box_len*(sin(DEG2RAD(45))),-0.02*box_len*(sin(DEG2RAD(45))),0.0f); 
	glVertex3f(0.02*box_len*(sin(DEG2RAD(45)))+(box_len*0.03),-0.02*box_len*(sin(DEG2RAD(45))),0.0f); 
	glEnd(); 
}
void drawsline4(float x,float y,float length,int fl)
{
	glLineWidth(2.5); 
	glTranslatef(x,y,-0.0f);
	if(fl==0)
	{
		glColor3f(1.0f, 0.0f, 0.0f);
	}
	else if(fl==1)
	{
		glColor3f(0.0f, 1.0f, 0.0f);
	}
	else
	{
		glColor3f(0.0f, 0.0f, 0.0f);
	}
	glBegin(GL_LINES); 
	glVertex3f(-0.02*box_len*(sin(DEG2RAD(45))),0.02*box_len*(sin(DEG2RAD(45))),0.0f); 
	glVertex3f(-0.02*box_len*(sin(DEG2RAD(45)))-(box_len*0.03),0.02*box_len*(sin(DEG2RAD(45))),0.0f); 
	glEnd(); 
}
void drawsline5(float x,float y,float length,int fl)
{
	glLineWidth(2.5); 
	glTranslatef(x,y,-0.0f);
	if(fl==0)
	{
		glColor3f(1.0f, 0.0f, 0.0f);
	}
	else if(fl==1)
	{
		glColor3f(0.0f, 1.0f, 0.0f);
	}
	else
	{
		glColor3f(0.0f, 0.0f, 0.0f);
	}
	glBegin(GL_LINES); 
	glVertex3f(length*(sin(DEG2RAD(45))),length*(sin(DEG2RAD(45))),0.0f); 
	glVertex3f(length*(sin(DEG2RAD(45)))+(box_len*0.03),length*(sin(DEG2RAD(45))),0.0f); 
	glEnd(); 
}
void drawsline6(float x,float y,float length,int fl)
{
	glLineWidth(2.5); 
	glTranslatef(x,y,-0.0f);
	if(fl==0)
	{
		glColor3f(1.0f, 0.0f, 0.0f);
	}
	else if(fl==1)
	{
		glColor3f(0.0f, 1.0f, 0.0f);
	}
	else
	{
		glColor3f(0.0f, 0.0f, 0.0f);
	}
	glBegin(GL_LINES); 
	glVertex3f(-length*(sin(DEG2RAD(45))),-length*(sin(DEG2RAD(45))),0.0f); 
	glVertex3f(-length*(sin(DEG2RAD(45)))-(box_len*0.03),-length*(sin(DEG2RAD(45))),0.0f); 
	glEnd(); 
}
void drawsline2(float x,float y,float length,int fl)
{
	glLineWidth(2.5); 
	glTranslatef(x,y,-0.0f);
	if(fl==0)
	{
		glColor3f(1.0f, 0.0f, 0.0f);
	}
	else if(fl==1)
	{
		glColor3f(0.0f, 1.0f, 0.0f);
	}
	else
	{
		glColor3f(0.0f, 0.0f, 0.0f);
	}
	glBegin(GL_LINES); 
	glVertex3f(length*(sin(DEG2RAD(45))),length*(sin(DEG2RAD(45))),0.0f); 
	glVertex3f(-length*(sin(DEG2RAD(45))),-length*(sin(DEG2RAD(45))),0.0f); 
	glEnd(); 
}


void drawsline11(float x,float y,float length,int fl)
{
	glLineWidth(2.5); 
	glTranslatef(x,y,-0.0f);
	if(fl==0)
	{
		glColor3f(1.0f, 0.0f, 0.0f);
	}
	else if(fl==1)
	{
		glColor3f(0.0f, 1.0f, 0.0f);
	}
	else
	{
		glColor3f(0.0f, 0.0f, 0.0f);
	}
	glBegin(GL_LINES); 
	glVertex3f(length*(sin(DEG2RAD(25))),-length*(sin(DEG2RAD(25))),0.0f); 
	glVertex3f(-length*(sin(DEG2RAD(25))),length*(sin(DEG2RAD(25))),0.0f); 
	glEnd(); 
}

void drawsline31(float x,float y,float length,int fl)
{
	glLineWidth(0.0); 
	glTranslatef(x,y,-0.0f);
	if(fl==0)
	{
		glColor3f(1.0f, 0.0f, 0.0f);
	}
	else if(fl==1)
	{
		glColor3f(0.0f, 1.0f, 0.0f);
	}
	else
	{
		glColor3f(0.0f, 0.0f, 0.0f);
	}
	glBegin(GL_LINES); 
	glVertex3f(0.02*box_len*(sin(DEG2RAD(25))),-0.02*box_len*(sin(DEG2RAD(25))),0.0f); 
	glVertex3f(0.02*box_len*(sin(DEG2RAD(25)))+(box_len*0.04),-0.02*box_len*(sin(DEG2RAD(25))),0.0f); 
	glEnd(); 
}
void drawsline41(float x,float y,float length,int fl)
{
	glLineWidth(0.0); 
	glTranslatef(x,y,-0.0f);
	if(fl==0)
	{
		glColor3f(1.0f, 0.0f, 0.0f);
	}
	else if(fl==1)
	{
		glColor3f(0.0f, 1.0f, 0.0f);
	}
	else
	{
		glColor3f(0.0f, 0.0f, 0.0f);
	}
	glBegin(GL_LINES); 
	glVertex3f(-0.02*box_len*(sin(DEG2RAD(25))),0.02*box_len*(sin(DEG2RAD(25))),0.0f); 
	glVertex3f(-0.02*box_len*(sin(DEG2RAD(25)))-(box_len*0.04),0.02*box_len*(sin(DEG2RAD(25))),0.0f); 
	glEnd(); 
}
void drawsline51(float x,float y,float length,int fl)
{
	glLineWidth(0.0); 
	glTranslatef(x,y,-0.0f);
	if(fl==0)
	{
		glColor3f(1.0f, 0.0f, 0.0f);
	}
	else if(fl==1)
	{
		glColor3f(0.0f, 1.0f, 0.0f);
	}
	else
	{
		glColor3f(0.0f, 0.0f, 0.0f);
	}
	glBegin(GL_LINES); 
	glVertex3f(length*(sin(DEG2RAD(25))),length*(sin(DEG2RAD(25))),0.0f); 
	glVertex3f(length*(sin(DEG2RAD(25)))+(box_len*0.04),length*(sin(DEG2RAD(25))),0.0f); 
	glEnd(); 
}
void drawsline61(float x,float y,float length,int fl)
{
	glLineWidth(0.0); 
	glTranslatef(x,y,-0.0f);
	if(fl==0)
	{
		glColor3f(1.0f, 0.0f, 0.0f);
	}
	else if(fl==1)
	{
		glColor3f(0.0f, 1.0f, 0.0f);
	}
	else
	{
		glColor3f(0.0f, 0.0f, 0.0f);
	}
	glBegin(GL_LINES); 
	glVertex3f(-length*(sin(DEG2RAD(25))),-length*(sin(DEG2RAD(25))),0.0f); 
	glVertex3f(-length*(sin(DEG2RAD(25)))-(box_len*0.04),-length*(sin(DEG2RAD(25))),0.0f); 
	glEnd(); 
}
void drawsline21(float x,float y,float length,int fl)
{
	glLineWidth(0.0); 
	glTranslatef(x,y,-0.0f);
	if(fl==0)
	{
		glColor3f(1.0f, 0.0f, 0.0f);
	}
	else if(fl==1)
	{
		glColor3f(0.0f, 1.0f, 0.0f);
	}
	else
	{
		glColor3f(0.0f, 0.0f, 0.0f);
	}
	glBegin(GL_LINES); 
	glVertex3f(length*(sin(DEG2RAD(25))),length*(sin(DEG2RAD(25))),0.0f); 
	glVertex3f(-length*(sin(DEG2RAD(25))),-length*(sin(DEG2RAD(25))),0.0f); 
	glEnd(); 
}


void drawBox(float len) {

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
	glVertex2f(-len / 2, -len / 2);
	glVertex2f(len / 2, -len / 2);
	glVertex2f(len / 2, len / 2);
	glVertex2f(-len / 2, len / 2);
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
void drawRectCG(float len1,float len2) {

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
	glColor3f(0.0f,(51.0/255),0.0f);
	glVertex2f(-len1/2 , -len2 );
	glColor3f(0.0f,(51.0/255),0.0f);
	glVertex2f(len1/2 , -len2 );
	glColor3f((178.0/255),(255.0/255),(102.0/255));
	glVertex2f(len1/2 , len2 );
	glColor3f((178.0/255),(255.0/255),(102.0/255));
	glVertex2f(-len1/2 , len2 );
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
void drawRectCR(float len1,float len2) {

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
	glColor3f((204.0/255),0.0f,0.0f);
	glVertex2f(-len1/2 , -len2 );
	glColor3f((204.0/255),0.0f,0.0f);
	glVertex2f(len1/2 , -len2 );
	glColor3f((255.0/255),(153.0/255),(153.0/255));
	glVertex2f(len1/2 , len2 );
	glColor3f((255.0/255),(153.0/255),(153.0/255));
	glVertex2f(-len1/2 , len2 );
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
void drawRectCG2(float len1,float len2) {

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
	glColor3f(0.0f,(51.0/255),0.0f);
	glVertex2f(-len1/2 , -len2 );
	glColor3f(0.0f,(51.0/255),0.0f);
	glVertex2f(len1/2 , -len2 );
	glColor3f(0.0f,(102.0/255),0.0f);
	glVertex2f(len1/2 , len2 );
	glColor3f(0.0f,(102.0/255),0.0f);
	glVertex2f(-len1/2 , len2 );
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
void drawRectCR2(float len1,float len2) {

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
	glColor3f((102.0/255),0.0f,0.0f);
	glVertex2f(-len1/2 , -len2 );
	glColor3f((102.0/255),0.0f,0.0f);
	glVertex2f(len1/2 , -len2 );
	glColor3f((204.0/255),0.0f,0.0f);
	glVertex2f(len1/2 , len2 );
	glColor3f((204.0/255),0.0f,0.0f);
	glVertex2f(-len1/2 , len2 );
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


void drawRect(float len1,float len2) {

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
	glVertex2f(-len1/2 , -len2 );
	glVertex2f(len1/2 , -len2 );
	glVertex2f(len1/2 , len2 );
	glVertex2f(-len1/2 , len2 );
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
void drawRect1(float len1,float len2) {

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
	glVertex2f(-len1/2 , -len2 );
	glVertex2f(len1/2 , -len2 );
	glVertex2f(len1/2 , len2 );
	glVertex2f(-len1/2 , len2 );
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


void drawCan(float len1,float len2) {

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
	glVertex2f(-len1/2 , -len2 );
	glVertex2f(len1/2 , -len2 );
	glVertex2f(len1/2 , len2 );
	glVertex2f(-len1/2 , len2 );
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
void drawUCan(float len1,float len2) {

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
	glVertex2f(-len1/2 , -len2*(kano*0.02f));
	glVertex2f(len1/2 , -len2*(kano*0.02f));
	glVertex2f(len1/2 , len2*(kano*0.02f));
	glVertex2f(-len1/2 , len2*(kano*0.02f));
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
void drawRCan(float len1,float len2) {

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
	glVertex2f(-(0.1*box_len)/2, -len2 );
	glVertex2f(-(0.1*box_len)/2-(box_len*0.01), -len2 );
	glVertex2f(-(0.1*box_len)/2-(box_len*0.01), len2 );
	glVertex2f(-(0.1*box_len)/2, len2 );
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
void drawLCan(float len1,float len2) {

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
	glVertex2f((box_len*0.1)/2, -len2 );
	glVertex2f((box_len*0.1)/2+(0.01*box_len), -len2 );
	glVertex2f((box_len*0.1)/2+(0.01*box_len), len2 );
	glVertex2f((box_len*0.1)/2, len2 );
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
void drawBall(float rad) {

	glBegin(GL_TRIANGLE_FAN);
	for(int i=0 ; i<360 ; i++) {
		glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
	}
	glEnd();
}

GLUquadricObj* myReusableQuadric = 0; 
void drawGluCylinder( float height, float radius, float slices, float stacks ) 
{
	if ( ! myReusableQuadric ) 
	{ 
		myReusableQuadric = gluNewQuadric(); 
		gluQuadricNormals( myReusableQuadric, GL_TRUE ); 
	} 
	gluCylinder( myReusableQuadric, radius, radius, height, slices, stacks ); 
}

void drawline(int i,int fl)
{
	glLineWidth(2.5); 
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES); 
	glVertex3f(laser[i].x,laser[i].y+(0.06*box_len)/2,0.0f); 
	glVertex3f(laser[i].x+0.4*(sin(DEG2RAD(-1*laser[i].theta))),(laser[i].y+(0.06*box_len)/2)+0.4*(cos(DEG2RAD(-1*laser[i].theta))),0.0f); 
	glEnd(); 
}
void drawl(int i)
{

	glLineWidth(2.5); 
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES); 
	glVertex3f(remain[i].x,remain[i].y+(0.06*box_len)/2,0.0f); 
	glVertex3f(remain[i].x+0.4*(sin(DEG2RAD(-1*remain[i].theta))),(remain[i].y+(0.06*box_len)/2)+0.4*(cos(DEG2RAD(-1*remain[i].theta))),0.0f); 
	glEnd(); 
}

void drawlinecan()
{
	glLineWidth(2.5); 
	glTranslatef(tri_x,tri_y,-0.0f);
	if(fblue)
	{
		glColor3f(0.25f,0.25f, 1.0f);
	}
	else
	{
		glColor3f(0.5f,0.5f, 1.0f);
	}
	glRotatef(theta,0.0f,0.0f,1.0f);
	glBegin(GL_LINES); 
	glVertex3f((box_len*0.1)/2,0.0,0.0f); 
	glVertex3f((-box_len*0.1)/2,0.0,0.0f); 
	glEnd(); 
}
void drawTriangle() {

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glEnd();
}

// Initializing some openGL 3D rendering options
void initRendering() {

	glEnable(GL_DEPTH_TEST);        // Enable objects to be drawn ahead/behind one another
	glEnable(GL_COLOR_MATERIAL);    // Enable coloring
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Setting a background color
}


// Function cnlled when the window is resized
void handleResize(int w, int h) {

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)w / (float)h, 0.1f, 200.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void handleKeypress1(unsigned char key, int x, int y) {

	if (key == 27) {
		over=1;
		system("aplay gameover.wav &");
		cout<<"Your Score Is :"<<cnt<<endl;
		//exit(0);     // escape key is pressed
	}
	if( key=='g')
	{
		if(fgreen==0 && pase==0)
		{
			fgreen=1;
			fred=0;
			fblue=0;
			glutSpecialFunc(handlegreen);
		}
	}
	if(key=='r')
	{
		if(fred==0 && pase==0)
		{
			fred=1;
			fgreen=0;
			fblue=0;
			glutSpecialFunc(handlered);
		}
	}
	if(key=='b')
	{
		if(fblue==0 && pase==0)
		{
			fblue=1;
			fred=0;
			fgreen=0;
			glutSpecialFunc(handleblue);
		}
	}
	if(key==' ')
	{
		if(kano==50 && fblue==1)
		{
			system("aplay shoot.wav &");
			t=0;
			kano=0;
			las ct;
			ct.x=tri_x;
			ct.y=tri_y;
			ct.vel=0.1f;
			ct.theta=theta;
			ct.col=0;
			laser.push_back(ct);
			ct.vel=0;
			ct.x=-4.0f;
			remain.push_back(ct);
		}
	}
	if(key=='p')
	{
		if(pase==0)
		{
			system("aplay pause.wav &");
			pase=2;
		}
		else
		{
			system("aplay pause.wav &");
			pase=0;
			glutTimerFunc(10, update, 0);	
			glutTimerFunc(1000,generate, 0);
			glutTimerFunc(12,ball_update, 0);
		}
	}
}


void handlegreen(int key,int x,int y){
	if (key == GLUT_KEY_LEFT)
	{
			if(green_x>gll)
			{
				green_x -= 0.1;
			}
	}
	if (key == GLUT_KEY_RIGHT)
	{
			if(green_x<glr)
			{
		green_x += 0.1;
			}
	}
}
void handlered(int key,int x,int y){
	if (key == GLUT_KEY_LEFT)
	{
			if(red_x>rll)
			{
		red_x -= 0.1;
			}
	}
	if (key == GLUT_KEY_RIGHT)
	{
			if(red_x<rlr)
			{
		red_x += 0.1;

			}
	}
}

void handleblue(int key,int x,int y){
	if (key == GLUT_KEY_LEFT)
	{
		if(tri_x>bll)
		{
			tri_x -= 0.1;
		}
	}
	if (key == GLUT_KEY_RIGHT)
	{
		if(blr>tri_x)
		{
			tri_x += 0.1;
		}
	}
	if (key == GLUT_KEY_UP)
	{
		if(theta<80)
		{
			theta+=10;
		}
	}
	if (key == GLUT_KEY_DOWN)
	{
		if(theta>-80)
		{
			theta-=10;
		}
	}
}


void handleKeypress2(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT)
		tri_x -= 0.1;
	if (key == GLUT_KEY_RIGHT)
		tri_x += 0.1;
}
void motionhandler(int x,int y)
{
	mousepos(x,y);
	if(pase==0 && over==0)
	{
		if(side==1)
		{
			if(mode==1 && mouseposx<(box_len/2-0.1*box_len/2) && mouseposx>(-box_len/2+0.1*box_len/2) && mouseposx>bll && mouseposx<blr)
			{
				tri_x=mouseposx;	
			}
			else if(mode==2 && (mouseposx)<(box_len/2-green_rad/2) && mouseposx>(-box_len/2+green_rad/2)&& mouseposx>gll && mouseposx<glr)
			{
				green_x=mouseposx;
			}
			else if(mode==3  && mouseposx<(box_len/2-red_rad/2) && mouseposx>(-box_len/2+red_rad/2) && mouseposx>rll && mouseposx<rlr)
			{
				red_x=mouseposx;
			}
		}
		else if(side==2)
		{
			if(mode==1)
			{

				float val=(-1*atan2(mouseposx-tri_x,mouseposy-tri_y)*(180/PI));
				if(val<80 && val>-80)
				{
					theta=val;
				}
			}
		}
	}
}
void handleMouseclick(int button, int state, int x, int y) {
	mousepos(x,y);
	if(mouseposx<=(tri_x+(0.1*box_len)/2) && mouseposx>=(tri_x-(0.1*box_len)/2) && mouseposy<=(tri_y+(box_len*0.06)/2) && mouseposy>=(tri_y-(box_len*0.06)/2))
	{
		mode=1;
	}

	else if(mouseposx<=(green_x+green_rad/2) && mouseposx>=(green_x-(green_rad)/2) && mouseposy<=(green_y+(green_height)/2) && mouseposy>=(green_y-(green_height)/2))
	{
		mode=2;
	}
	else if(mouseposx<=(red_x+red_rad/2) && mouseposx>=(red_x-(red_rad)/2) && mouseposy<=(red_y+(red_height)/2) && mouseposy>=(red_y-(red_height)/2))
	{
		mode=3;
	}
	if(mode==1)
	{
		if (state == GLUT_DOWN)
		{
			fblue=1;
			if (button == GLUT_LEFT_BUTTON)
			{
				side=1;
			}
			if(button == GLUT_RIGHT_BUTTON)
			{
				side=2;
			}
		}
		else
		{
			mode=0;
			fblue=0;
		}
	}
	if(mode==2)
	{
		if (state == GLUT_DOWN)
		{
			fgreen=1;
			if (button == GLUT_LEFT_BUTTON)
			{
				side=1;
			}
			if(button == GLUT_RIGHT_BUTTON)
			{
				side=2;
			}
		}
		else
		{
			mode=0;
			fgreen=0;
		}
	}
	if(mode==3)
	{
		if (state == GLUT_DOWN)
		{
			fred=1;
			if (button == GLUT_LEFT_BUTTON)
			{
				side=1;
			}
			if(button == GLUT_RIGHT_BUTTON)
			{
				side=2;
			}
		}
		else
		{
			mode=0;
			fred=0;
		}
	}
}
