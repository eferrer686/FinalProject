
#include<cstdlib>
#include <stdio.h>
#include <string.h>
#include "Player.h"


Player::Player(float _r, float _g, float _b)
{
    r = _r;
    g = _g;
    b = _b;

	posX = r;
	posZ = b;

	radius = 0.5;
    

}

Player::~Player()
{
    
}

void Player::update()
{
    if (Right == 1)
    {

        posX+=0.1;
        
        Right = 0;
    }
    
    if (Up == 1)
    {
      
        posZ -= 0.1;
    
        Up = 0;
    }
    
    
    if (Down == 1)
    {
     
        posZ += 0.1;
        
        Down = 0;
    }
    
    
    if (Left == 1)
    {
        posX -= 0.1;
        Left = 0;
    }
    
    
    
}

void Player::draw()
{

	glPushMatrix();
	{
		//renderColor();
		//Head
		glTranslatef(posX, posY, posZ);

		glutSolidSphere(radius, 10, 10);

		//Shoulder 1
		glPushMatrix();
		{
			glTranslatef(-radius, 0, 0);

			glutSolidSphere(radius / 2, 10, 10);
			//Hand 1
			glTranslatef(-radius / 2, 0, 0);

			glutSolidSphere(radius / 4, 10, 10);
		}
		glPopMatrix();

		//Shoulder 2
		glPushMatrix();
		{
			glTranslatef(radius, 0, 0);

			glutSolidSphere(radius / 2, 10, 10);
			//Hand 2
			glTranslatef(radius / 2, 0, 0);

			glutSolidSphere(radius / 4, 10, 10);
		}
		glPopMatrix();

	}
	glPopMatrix();
}


void Player::renderColor() {
	ka0 = new GLfloat[4];
	ka0[0] = .25f;
	ka0[1] = .15f;
	ka0[2] = .98f;
	ka0[3] = 1.0f;
	kd0 = new GLfloat[4];
	kd0[0] = .95f;
	kd0[1] = .15f;
	kd0[2] = .08f;
	kd0[3] = 1.0f;

	ks0 = new GLfloat[4];
	ks0[0] = .25f;
	ks0[1] = .15f;
	ks0[2] = .98f;
	ks0[3] = 1.0f;
	alpha0 = new GLfloat[1];
	alpha0[0] = 75.0f;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ka0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, kd0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ks0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_POSITION, alpha0);
}