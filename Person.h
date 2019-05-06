#pragma once
#include "Point.h"

class Person
{
public:
	Person(float _x, float _y, float _z, float _r, float _g, float _b);
	Person(Point* p);
	~Person();


	float x, y, z, r, g, b,xp,zp;
	int n, i;
	Point** ctrlPoints;
	float coefficients;
	Point* evaluate(float t);

	Point* multiplyByScalar(float _k);



	float calculateCoefficients(float n, float i);
	float factorial(float n);

	void setup();
	void draw();

	bool collide(Person* p);

		
};

