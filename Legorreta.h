#include "glm.h"

class Legorreta
{
public:


	GLfloat* Ia;
	GLfloat* Id;
	GLfloat* Is;
	GLfloat* Ip;

	GLMmodel* sintel;
	float* pos;
	float* dims;
	float* center;
	void draw();
	float sintel_pos[3];
	float sintel_dims[3];
	float radius;
	float mode;

	Legorreta();
	~Legorreta();

};