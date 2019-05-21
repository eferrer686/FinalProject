/*
 * Sergio Ruiz.
 *
 * TC3022. Computer Graphics Course.
 * Transformations exercise template.
 */

#pragma once
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#else
#include "freeglut.h"
#include <time.h>
#include <stdio.h>
#include <math.h>

#endif

#pragma once


class Player
{
public:
    Player(float r, float g, float b);
    ~Player();
    
    void draw();
	void renderColor();
    void update();
    //bool checkCupCollision(Particle* other);
    
    float side;
    float r;
    float g;
    float b;
	float radius;
    
    int Right = 0; //key right
    int Left = 0; //key left
    int Up = 0; //key up
    int Down = 0; //key down

	GLfloat* ka0;
	GLfloat* kd0;
	GLfloat* ks0;
	GLfloat* alpha0;
    float posX = 0;
    float posY = 0;
    float posZ = 0;
    
    
    
};

