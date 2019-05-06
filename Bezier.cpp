#include "Bezier.h"
#include <iostream>
#include <string>
using namespace std;

Bezier::Bezier(int _degree, Point**_ctrlPoints)
{
	degree = _degree;
	ctrlPoints = new Point*[degree];
	
	//copy the control points:
	for (int i = 0; i <= degree; i++) {
		Point* p = _ctrlPoints[i];
		ctrlPoints[i]= new Point(p);
		ctrlPoints[i]->calculateCoefficients(degree, i);
	}
}


Bezier::~Bezier()
{
	delete ctrlPoints;
}

Point * Bezier::evaluate(float t)
{
	Point* bez = new Point(0, 0, 0, 0.0f, 0.0f, 1.0f);
	Point* tempP = new Point(0,0,0,0,0,0);
	for (int i = 0; i <= degree; i++) {
				
		tempP = ctrlPoints[i]->evaluate(t);

		bez->x = tempP->x + bez->x;
		bez->y = tempP->y + bez->y;
		bez->z = tempP->z + bez->z;
	}
	
	return bez;
}

void Bezier::calculateCoefficients()
{
}

int Bezier::factorial(int n)
{
	if (n == 0) return 1;
	else return n * factorial(n - 1);
}
