#pragma once
#include "vecs.h"

class Camera
{
public:
	Camera();
	void setView();
	void move(float dir,float angle);
	void moveAround(float angle,vector3f p);
	void rotate(float angle, vector3f p);

	bool pointInFrustrum(float* p);

	vector3f pos;
	vector3f dir;
	vector3f up;
	vector3f pivot;
	float near_plane;
	float far_plane;
	float fov;
};