#pragma once

#include "global.h"
#include "Vector3.cpp"
#include "renderable.cpp"

class Sphere : protected Renderable {
public:
	float radius;
	Sphere(Vector3f pos, float rad, SurfaceProperties props) : Renderable(pos, props), radius(radius) {}
	virtual bool intersect(Vector3f &rayOrigin, Vector3f &rayDirection, float & distance) {
		Vector3f toCenter = this->position - rayOrigin;
		float tca = toCenter.dot(rayDirection);
		if (tca < 0) return false;
		float d2 = toCenter.lengthSquared() - tca*tca;
		if (d2 > radius*radius) return false;
		float thc = sqrt(radius*radius - d2);
		distance = tca - thc;
	}
};