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

#define CTRL_POINTS 5

unsigned int  texture_id = 0;

Bezier* bez;
Point* ctrl[CTRL_POINTS+2];
Person* traveler;
float param;				//time step
float dir;					//direction in time

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
	glEnable(GL_DEPTH_TEST);			// Enable check for close and far objects.
	glClearColor(0.0, 0.0, 0.0, 0.0);	// Clear the color state.
	glMatrixMode(GL_MODELVIEW);			// Go to 3D mode.
	glLoadIdentity();					// Reset 3D view matrix.


	float x1 = -5;
	float z1 = -5;
	float x2 = 5;
	float z2 = 5;

	ctrl[0] = new Point(x1, 0, z1, 0, 1, 0);	//Begin point
	ctrl[CTRL_POINTS+1] = new Point(x2, 0, z2, 0, 0, 1);	//Goal point
	
	float xr = 0;		//random in x
	float zr = 0;		//random in z

	//Generate Points in random position between begin and end
	for (int i = 1; i < CTRL_POINTS+1; i++)
	{
		xr = x1 + fabs(x1-x2) * ((float)rand()) / (float)RAND_MAX;
		zr = z1 + fabs(z1-z2) * ((float)rand()) / (float)RAND_MAX;
		ctrl[i] = new Point(xr, 0, zr, 1, 0, 0);
	}

	//Create bezier

	dir = 1;
	param = 0.0001;

	traveler = new Person(0, 0, 0, 0, 1, 0);
	bez = new Bezier(CTRL_POINTS+1, ctrl);
}

void display()							// Called for each frame (about 60 times per second).
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);				// Clear color and depth buffers.
	glLoadIdentity();												// Reset 3D view matrix.
	gluLookAt(0.10, 25.1, 0.10,										// Where the camera is.
		      0.0, 0.0, 0.0,										// To where the camera points at.
		      0.0, 1.0, 0.0);										// "UP" vector.

	axes();

	//Draw points
	for (int i = 0; i <= CTRL_POINTS+1; i++)
	{
		ctrl[i]->draw();
	}


	//Calculate traveler position
	traveler = new Person(bez->evaluate(param));
	//Draw position
	traveler->draw();
	delete traveler;

	//Reverse dir if end of path
	if (param <= 0) { param = 0.001; dir *= -1; }
	if (param >= 1) { param = 0.999; dir *= -1; }

	//Next step
	param += 0.0001f * dir;

	glutSwapBuffers();												// Swap the hidden and visible buffers.


}
void idle()															// Called when drawing is finished.
{
	glutPostRedisplay();											// Display again.
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


	glutReshapeFunc(reshape);										// Reshape CALLBACK function.
	glutDisplayFunc(display);										// Display CALLBACK function.
	glutIdleFunc(idle);												// Idle CALLBACK function.
	glutMainLoop();													// Begin graphics program.
	return 0;														// ANSI C requires a return value.
}
