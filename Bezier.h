#pragma once
#include "Point.h"
class Bezier
{
public:
	Bezier(int _degree, Point** ctrlPoints);
	//Point**_ctrlPoints is a pointer to an array of control points.
	~Bezier();
	//evaluate: returns a point on the Bezier curve for parameter "t".
	Point* evaluate(float t);
	void calculateCoefficients();
	int factorial(int n);

	int degree;
	Point** ctrlPoints;
	float* coefficients;
};

