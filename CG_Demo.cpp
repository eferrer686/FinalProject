/*
 * Sergio Ruiz.
 *
 * TC3022. Computer Graphics Course.
 * Basic template OpenGL project.
 */

// Please don't change lines 9-31 (It helps me to grade)
#ifdef __APPLE__
// For XCode only: New C++ terminal project. Build phases->Compile with libraries: add OpenGL and GLUT
// Import this whole code into a new C++ file (main.cpp, for example). Then run.
// Reference: https://en.wikibooks.org/wiki/OpenGL_Programming/Installation/Mac
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	#include <GLUT/glut.h>
#endif
#ifdef _WIN32
// For VS on Windows only: Download CG_Demo.zip. UNZIP FIRST. Double click on CG_Demo/CG_Demo.sln
// Run
	#include "freeglut.h"
#endif
#ifdef __unix__
// For Linux users only: g++ CG_Demo.cpp -lglut -lGL -o CG_Demo
// ./CG_Demo
// Reference: https://www.linuxjournal.com/content/introduction-opengl-programming
	#include "GL/freeglut.h"
	#include "GL/gl.h"
#endif

#include <stdio.h>
#include <math.h>
#include "Bezier.h"
#include "Point.h"
#include "Person.h"
#include "CG_Demo.h"
#include "Legorreta.h"
#include "Player.h"
#include "Camera.h"

#define CTRL_POINTS 5
#define NUM_ALUMNOS 99  //Multiplos de 3

unsigned int  texture_id = 0;

Person* alumnos[NUM_ALUMNOS];
float param;				//time step
float dir;					//direction in time

Player* player;

int mouseCoords[2], mouseMotionType = 0;
Camera* mainCam;

Legorreta* lego;

GLfloat* Ia;
GLfloat* Id;
GLfloat* Is;
GLfloat* Ip;
GLfloat* global_ambient;


void axes() {
	glLineWidth(5.0f);
	glBegin(GL_LINES);
	{
		glColor3f(1, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(1, 0, 0);

		glColor3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 1, 0);

		glColor3f(0, 0, 1);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 1);
		
	}
	glEnd();
}



void init() // FOR GLUT LOOP
{


	mainCam = new Camera();

	//3 different starting points only 1 goal
	float goalx = -30;
	float goalz = 0;

	float p1x = 10;
	float p1z = 0;

	float p2x = 0;
	float p2z = -20;


	float p3x = 0;
	float p3z = 20;

	for (int i = 0; i < NUM_ALUMNOS/3; i++)
	{
		Point* pi = new Point(goalx+(i/NUM_ALUMNOS), 0, goalz+(i/NUM_ALUMNOS), 1, 1, 1);
		Point* pf = new Point(p1x, 0, p1z, 1, 1, 1);
		
		
		alumnos[i] = new Person(pi, pi, pf);
		alumnos[i]->param = 0.5;
	}

	for (int i = (NUM_ALUMNOS / 3); i < (2*NUM_ALUMNOS) / 3; i++)
	{
		Point* pi = new Point(goalx + (i / NUM_ALUMNOS), 0, goalz + (i / NUM_ALUMNOS), 1, 1, 1);
		Point* pf = new Point(p2x, 0, p2z, 1, 1, 1);


		alumnos[i] = new Person(pi, pi, pf);
		alumnos[i]->param = 0.5;
	}

	for (int i = ((2*NUM_ALUMNOS) / 3); i < (3 * NUM_ALUMNOS) / 3; i++)
	{
		Point* pi = new Point(goalx + (i / NUM_ALUMNOS), 0, goalz + (i / NUM_ALUMNOS), 1, 1, 1);
		Point* pf = new Point(p3x, 0, p3z, 1, 1, 1);


		alumnos[i] = new Person(pi, pi, pf);
		alumnos[i]->param = 0.5;
	}

	lego = new Legorreta();
	
	player = new Player(goalx, 0, goalz);		//You´re the big guy
	


	
	glLoadIdentity(); // Reset 3D view matrix.

}

void display()							// Called for each frame (about 60 times per second).
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);				// Clear color and depth buffers.

	axes();

	mainCam->setView();

	lego->draw();

	player->draw();
	
	//Draw alumnos
	bool flagCollide = false;
	for (int i = 0; i < NUM_ALUMNOS; i++)
	{

		alumnos[i]->draw();
		
		if (alumnos[i]->collidePlayer(player)) {
			
			alumnos[i]->dir *= -1;
			flagCollide = true;
		}

		for (int j = 0; j < NUM_ALUMNOS; j++)
		{
			
			if (!flagCollide && i!=j) {
				flagCollide = alumnos[i]->collide(alumnos[j]);

			}

		}
		flagCollide = false;
	}

	

	glutSwapBuffers();												// Swap the hidden and visible buffers.


}
void idle()															// Called when drawing is finished.
{
	player->update();

	glutPostRedisplay();											// Display again.
}
void keys(int key, int x, int y)
{

	switch (key)
	{
	case GLUT_KEY_LEFT:
		// izquierda
		player->Left = 1;

		break;

	case GLUT_KEY_DOWN:
		//  abajo
		player->Down = 1;

		break;

	case GLUT_KEY_RIGHT:
		// derecha
		player->Right = 1;

		break;

	case GLUT_KEY_UP:
		// arriba
		player->Up = 1;

		break;

	}

}

void motion(int x, int y) {
	switch (mouseMotionType)
	{
	case 1:	//FREE
		mainCam->rotate((mouseCoords[0] - x)*-0.1, vector3f(0, 1, 0));
		mainCam->rotate((mouseCoords[1] - y)*-0.1, vector3f(1, 0, 0));
		mouseCoords[0] = x;
		mouseCoords[1] = y;
		break;
	case 2:	//SHIFT
		mainCam->moveAround((mouseCoords[0] - x)*0.1, vector3f(0, 1, 0));
		mainCam->moveAround((mouseCoords[1] - y)*0.1, vector3f(1, 0, 0));
		break;
	case 3:	//ALT

		break;
	case 4:	//CTRL

		break;
	default:
		break;
	}
}
void mouse(int button, int state, int x, int y) {
	int mods;
	mouseCoords[0] = x;
	mouseCoords[1] = y;
	if (state == GLUT_DOWN) {
		if (button == GLUT_LEFT_BUTTON) {

		}
		else if (button == GLUT_RIGHT_BUTTON) {

		}
		else {

		}
		mods = glutGetModifiers();

		if (mods & GLUT_ACTIVE_SHIFT) {
			mouseMotionType = 2;
		}
		else if (mods & GLUT_ACTIVE_ALT) {
			mouseMotionType = 3;
		}
		else if (mods & GLUT_ACTIVE_CTRL) {
			mouseMotionType = 4;
		}
		else {
			mouseMotionType = 1;
		}

	}
}


void reshape(int x, int y)											// Called when the window geometry changes.
{
	glMatrixMode(GL_PROJECTION);									// Go to 2D mode.
	glLoadIdentity();												// Reset the 2D matrix.
	gluPerspective(40.0, (GLdouble)x / (GLdouble)y, 0.5, 50.0);		// Configure the camera lens aperture.
	glMatrixMode(GL_MODELVIEW);										// Go to 3D mode.
	glViewport(0, 0, x, y);											// Configure the camera frame dimensions.
	gluLookAt(0.0, 1.0, 4.0,
		      0.0, 0.0, 0.0,
		      0.0, 1.0, 0.0);
	display();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);											// Init GLUT with command line parameters.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);		// Use 2 buffers (hidden and visible). Use the depth buffer. Use 3 color channels.
	glutInitWindowSize(800, 800);
	glutCreateWindow("RTS");

	
	init();

	glutSpecialFunc(keys);
	glutMotionFunc(motion);
	glutMouseFunc(mouse);

	glutReshapeFunc(reshape);										// Reshape CALLBACK function.
	glutDisplayFunc(display);										// Display CALLBACK function.
	glutIdleFunc(idle);												// Idle CALLBACK function.
	glutMainLoop();													// Begin graphics program.
	return 0;														// ANSI C requires a return value.
}
