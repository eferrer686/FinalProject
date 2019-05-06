#pragma once

class Point
{
public:
	Point(float _x, float _y, float _z, float _r, float _g, float _b);
	Point(Point* p);
	~Point();


	float x, y, z, r, g, b;
	int n, i;
	Point** ctrlPoints;
	float coefficients;
	Point* evaluate(float t);

	Point* multiplyByScalar(float _k);



	float calculateCoefficients(float n, float i);
	float factorial(float n);

	void setup();
	void draw();

	bool collide(Point* p);

		
};

