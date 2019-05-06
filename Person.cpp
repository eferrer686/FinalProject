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



Person::Person(float _x, float _y, float _z, float _r, float _g, float _b)
{
	x = _x;
	y = _y;
	z = _z;
	r = _r;
	g = _g;
	b = _b;
	xp = x;
	zp = z;
	

}

Person::Person(Point* p)
{

	x = p->x;
	y = p->y;
	z = p->z;
	r = 1;
	g = 1;
	b = 1;
	
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
	Point* p = new Point(x, y, z, r, g, b);
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


void Person::draw() {

	glPushMatrix();
	{
		//Head
		glTranslatef(x, y, z);
		glColor3f(r, g, b);
		glutSolidSphere(0.5, 10, 10);

		//Shoulder 1
		glPushMatrix();
		{
			glTranslatef(-0.5, 0, 0);
			glColor3f(r, g, b);
			glutSolidSphere(0.25, 10, 10);
			//Hand 1
			glTranslatef(-0.25, 0, 0);
			glColor3f(r, g, b);
			glutSolidSphere(0.125, 10, 10);
		}
		glPopMatrix();
		
		//Shoulder 2
		glPushMatrix();
		{
			glTranslatef(0.5, 0, 0);
			glColor3f(r, g, b);
			glutSolidSphere(0.25, 10, 10);
			//Hand 2
			glTranslatef(0.25, 0, 0);
			glColor3f(r, g, b);
			glutSolidSphere(0.125, 10, 10);
		}
		glPopMatrix();
		
	}
	glPopMatrix();
}

bool Person::collide(Person* p) {
	if (x + 0.1 < p->x && x - 0.1 > p->x 
		&& z + 0.1 < p->z && z - 0.1 > p->z)
	{
		return true;
	}
	else {
		return false;
	}
}