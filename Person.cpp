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
#include <iostream>
#include <cmath>

#include <string>
using namespace std;


#define __CUBE

#include "Person.h"
#include "Point.h"



Person::Person(Point* p,Point* _pi,Point* _pf)
{
	pos = p;

	pi = _pi;
	pf = _pf;

	r = g = b = 1.0f;

	radius = 0.2f;
	genRoute(pi,pf);

	

}


Person::~Person()
{
}

Point* Person::evaluate(float t)
{
	float k = coefficients * pow((1 - t), (n - i)) * pow(t,i);
	
	return multiplyByScalar(k);
	
}


Point* Person::multiplyByScalar(float _k){
	Point* p = new Point(p->x, p->y, p->z, p->r, p->g, p->b);
	p->x*= _k;
	p->y*= _k;
	p->z*= _k;
	return p;
}

float Person::calculateCoefficients(float _n, float _i) {
	n = _n;
	i = _i;
	float coefTemp = factorial(n) / (factorial(i)*factorial(n - i));
	coefficients = coefTemp;
	return coefTemp;
}

float Person::factorial(float n)
{
	if (n == 0) {
		return 1;
	}
	else {
		return factorial(n - 1) * n;
	}
}

void Person::genRoute(Point *pi, Point *pf) {
	float x1 = pi->x;
	float z1 = pi->z;
	float x2 = pf->x;
	float z2 = pf->z;

	ctrl[0] = new Point(x1, 0, z1, 0, 1, 0);	//Begin point
	ctrl[CTRL_POINTS + 1] = new Point(x2, 0, z2, 0, 0, 1);	//Goal point

	float xr = 0;		//random in x
	float zr = 0;		//random in z

	//Generate Points in random position between begin and end
	for (int i = 1; i < CTRL_POINTS + 1; i++)
	{
		xr = x1 + fabs(x1 - x2) * ((float)rand()) / (float)RAND_MAX;
		zr = z1 + fabs(z1 - z2) * ((float)rand()) / (float)RAND_MAX;
		ctrl[i] = new Point(xr, 0, zr, 1, 0, 0);
	}

	//Create bezier

	dir = 1;
	param = 0.0001;

	bez = new Bezier(CTRL_POINTS + 1, ctrl);

}

void Person::draw() {

	pos = bez->evaluate(param);

	//Reverse dir if end of path
	if (param <= 0) { param = 0.001; dir *= -1; }
	if (param >= 1) { param = 0.999; dir *= -1; }

	//Next step
	param += 0.0005f * dir;
	   	 
	//Draw points
	/*for (int i = 0; i <= CTRL_POINTS + 1; i++)
	{
		ctrl[i]->draw();
	}*/


	glPushMatrix();
	{
		//renderColor();
		//Head
		glTranslatef(pos->x, pos->y, pos->z);
		
		glutSolidSphere(radius, 10, 10);

		//Shoulder 1
		glPushMatrix();
		{
			glTranslatef(-radius, 0, 0);
			
			glutSolidSphere(radius/2, 10, 10);
			//Hand 1
			glTranslatef(-radius/2, 0, 0);
			
			glutSolidSphere(radius/4, 10, 10);
		}
		glPopMatrix();
		
		//Shoulder 2
		glPushMatrix();
		{
			glTranslatef(radius, 0, 0);
			
			glutSolidSphere(radius/2, 10, 10);
			//Hand 2
			glTranslatef(radius/2, 0, 0);
			
			glutSolidSphere(radius/4, 10, 10);
		}
		glPopMatrix();
		
	}
	glPopMatrix();
}

bool Person::collide(Person* p) {
	
	float dist = 0.0;

	dist = ((p->pos->x - pos->x)*(p->pos->x - pos->x)) + ((p->pos->z - pos->z)*(p->pos->z - pos->z));
	dist = sqrt(dist);

	if (dist < radius +(radius*0.4))
	{
		
		changeRoute();
		dir *= -1;
		return true;
	}
	else {
		return false;
	}
}

bool Person::collidePlayer(Player* p) {

	float dist = 0.0;

	dist = ((p->posX - pos->x)*(p->posX - pos->x)) + ((p->posZ - pos->z)*(p->posZ - pos->z));
	dist = sqrt(dist);

	if (dist < radius + (radius*3))
	{
		return true;
	}
	else {
		return false;
	}
}

void Person::changeRoute() {
	

	int indexI = floorf(CTRL_POINTS * ((float)rand()) / (float)RAND_MAX);
	int indexF = floorf(CTRL_POINTS * ((float)rand()) / (float)RAND_MAX);

	Point* temp = ctrl[indexI];
	ctrl[indexI] = ctrl[indexF];
	ctrl[indexF] = temp;

	genRoute(ctrl[indexI],ctrl[CTRL_POINTS+1]);


}

void Person::renderColor() {
	ka0 = new GLfloat[4];
	ka0[0] = .6f;
	ka0[1] = .6f;
	ka0[2] = .6f;
	ka0[3] = 1.0f;
	kd0 = new GLfloat[4];
	kd0[0] = .5f;
	kd0[1] = .5f;
	kd0[2] = .5f;
	kd0[3] = 1.0f;

	ks0 = new GLfloat[4];
	ks0[0] = .5f;
	ks0[1] = .5f;
	ks0[2] = .5f;
	ks0[3] = 1.0f;
	alpha0 = new GLfloat[1];
	alpha0[0] = 20.0f;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ka0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, kd0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ks0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_POSITION, alpha0);
}