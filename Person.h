#pragma once
#include "Point.h"
#include "Bezier.h"
#include "Player.h"

#define CTRL_POINTS 5

class Person
{
public:
	
	Person(Point * p, Point * _pi, Point * _pf);

	~Person();

	GLfloat* ka0;
	GLfloat* kd0;
	GLfloat* ks0;
	GLfloat* alpha0;


	int n, i;
	Point** ctrlPoints;
	float coefficients;
	Point* evaluate(float t);

	Point* pi;
	Point* pf;


	Point* multiplyByScalar(float _k);

	Point* pos;

	Bezier* bez;
	Point* ctrl[CTRL_POINTS + 2];
	Person* traveler;
	float param;				//time step
	float dir;					//direction in time

	float r, g, b;
	float radius;

	float calculateCoefficients(float n, float i);
	float factorial(float n);

	void genRoute(Point * pi, Point * pf);


	void setup();
	void draw();

	bool collide(Person* p);

	bool collidePlayer(Player * p);

	void changeRoute();

	void renderColor();

		
};

