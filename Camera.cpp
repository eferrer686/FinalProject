#include "..\header\Camera.h"
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
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>

Camera::Camera() {
	pos.x = 0;
	pos.y = 0;
	pos.z = 30;

	dir.x = 0;
	dir.y = 0;
	dir.z = -1;

	up.x = 0;
	up.y = 1;
	up.z = 0;

	pivot.x = pivot.y = pivot.z = 0;

	near_plane = 1.0;
	far_plane = 100;

	fov = 45;
}

void Camera::setView()
{
	int viewportCoords[4];
	glGetIntegerv(GL_VIEWPORT, viewportCoords);

	glMatrixMode(GL_PROJECTION); // GO to 2d Mode
	glLoadIdentity(); //Reset
	gluPerspective(fov,(GLfloat)viewportCoords[2]/ (GLfloat)viewportCoords[3],near_plane,far_plane);

	glMatrixMode(GL_MODELVIEW);	//Go to 3d Mode
	glLoadIdentity(); //Reset
	gluLookAt(
		pos.x, pos.y, pos.z,							//Position of camera
		pos.x + dir.x, pos.y + dir.y, pos.z + dir.z,	//Looking to this position
		up.x, up.y, up.z								//what is "up"
	);
}

void Camera::move(float dist, float angle)
{
	vector3f right;
	vector3f moveDir;
	float cosAng, sinAng, radAng;
	radAng = angle * M_PI / 180.0;
	cosAng = cos(radAng);
	sinAng = sin(radAng);
	
	float d[] = { dir.x, dir.y, dir.z };
	float u[] = { up.x,up.y,up.z };
	float r[] = { right.x,right.y,right.z };

	crossProduct(d,u,r); //r = d x u

	moveDir.x = d[0] * cosAng - r[0] *sinAng;
	moveDir.x = d[1] * cosAng - r[1] * sinAng;
	moveDir.x = d[2] * cosAng - r[2] * sinAng;

	pos.x += dist * moveDir.x;
	pos.y += dist * moveDir.y;
	pos.z += dist * moveDir.z;


}

void Camera::moveAround(float angle, vector3f axis)
{
	float d[] = { dir.x,dir.y,dir.z };
	float u[] = { up.x,up.y,up.z };
	float r[] = { 0,0,0 };
	crossProduct(d, u, r);
	float a[] = { axis.x,axis.y, axis.z };
	//float oa[] = { axis.x,axis.y, axis.z };
	unitVector(a);

	float negPos[] = { pos.x - pivot.x,pos.y - pivot.y, pos.z - pivot.z };
	float distPivot = vecMagnitude(negPos);
	unitVector(negPos);
	float radAng = DEGTORAD(angle);
	float newPos[] = { 0,0,0 };
	float newDir[] = { 0,0,0 };
	float newUp[] = { 0,0,0 };

	rotatePointAroundAxis(negPos,a,radAng,newPos);
	rotatePointAroundAxis(d, a, radAng, newDir);
	rotatePointAroundAxis(u, a, radAng, newUp);

	pos.set(pivot.x + newPos[0]*distPivot, pivot.y + newPos[1] * distPivot, pivot.z + newPos[2] * distPivot);
	dir.set(newDir[0], newDir[1], newDir[2]);
	up.set(newUp[0], newUp[1], newUp[2]);


}

void Camera::rotate(float angle, vector3f axis)
{
	float ax[] = { axis.x,axis.y,axis.z };
	unitVector(ax);
	float radAng = DEGTORAD(angle);
	float d[] = { dir.x,dir.y,dir.z };
	float newD[] = { 0,0,0 };
	rotatePointAroundAxis(d, ax, radAng, newD);

	float u[] = { up.x,up.y,up.z };
	float newU[] = { 0,0,0 };
	rotatePointAroundAxis(u, ax, radAng, newU);

	dir.set(newD[0], newD[1], newD[2]);
	up.set(newU[0], newU[1], newU[2]);

}

bool Camera::pointInFrustrum(float* p)
{
	vector3f right;



	float d[] = { dir.x,dir.y,dir.z };	//Z
	float u[] = { up.x,up.y,up.z };		//Y
	float r[] = { right.x,right.y,right.z }; //X

	crossProduct(d, u, r); //r = d x u

	float v[] = { p[0]-dir.x,p[1]-dir.y,p[2]-dir.z };	//V

	
	int viewportCoords[4];
	glGetIntegerv(GL_VIEWPORT, viewportCoords);
	float ratio = viewportCoords[2] / viewportCoords[3];

	float tang = tan(DEGTORAD(fov*0.5));

	float dpz = dotProduct(p, d);

	float h = dpz * tang;  //	h/2
	float w = h * ratio;	// w/2
	
	float proy = dotProduct(d, v);

	if (proy<near_plane || proy >far_plane) {
		return false;
	}

	proy = dotProduct(d, u);
	if (proy< -h/2 || proy >h/2) {
		return false;
	}
	
	proy = dotProduct(d, r);
	if (proy< -w/2 || proy >w/2) {
		return false;
	}

	return true;

	
}
