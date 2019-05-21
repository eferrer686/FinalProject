#include "Legorreta.h"

Legorreta::Legorreta()
{
	//sintel = glmReadOBJ("assets/modelo/Tec.obj");
	sintel = glmReadOBJ("assets/Legorretafinal.obj");
	
	mode = 0;
	radius = 0;
	sintel_pos[0] = 0.0f;
	sintel_pos[1] = 0.0f;
	sintel_pos[2] = 0.0f;


	glmUnitize(sintel);
	glmFacetNormals(sintel);
	glmDimensions(sintel, sintel_dims);

	float center[3] = { sintel_pos[0] + sintel_pos[0] / 2.0f,
						sintel_pos[1] + sintel_pos[1] / 2.0f,
						sintel_pos[2] + sintel_pos[2] / 2.0f };

	radius = sqrtf(center[0] * center[0] + center[1] * center[1] + center[2] * center[2]);

	//Lights for render

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat diffusel0[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat ambientl0[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat specularl0[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat position[4] = { 0.0f, 30.5f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientl0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffusel0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularl0);
	glLightfv(GL_LIGHT0, GL_POSITION, position);


	GLfloat*	global_ambient;
	global_ambient = new GLfloat[4];
	global_ambient[0] = 0.3f;
	global_ambient[1] = 0.3f;
	global_ambient[2] = 0.3f;
	global_ambient[3] = 1.0f;
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
}


Legorreta::~Legorreta() {}

void Legorreta::draw() {
	glPushMatrix();
	{
		glScalef(100, 100, 100);
		glTranslatef(sintel_pos[0], sintel_pos[1]+0.035f, sintel_pos[2]);
		//glRotatef(180, 1, 0, 0);
		//glmDraw(sintel, GLM_FLAT);
		glmDraw(sintel, GLM_SMOOTH | GLM_TEXTURE);		//No idea why texture isn´t displayed
	}
	glPopMatrix();
}