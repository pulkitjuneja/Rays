#pragma once

#include "global.h"
#include "Vector3.cpp"
#include "renderable.cpp"

class Sphere : public Renderable
{
  public:
	float radius;
	Sphere(Vector3f pos, float rad, Material props) : Renderable(pos, props), radius(rad) {}
	virtual bool intersects(Vector3f &rayOrigin, Vector3f &rayDirection, float &distance)
	{
		Vector3f toCenter = center - rayOrigin;
		float tca = toCenter.dot(rayDirection);
		if (tca < 0)
			return false;
		float d2 = toCenter.lengthSquared() - tca * tca;
		if (d2 > radius * radius)
			return false;
		float thc = sqrt(radius * radius - d2);
		distance = tca - thc;
		return false;
	}
	virtual void getProperties(Vector3f &hitpoint, Vector3f &dir, int &index, Vector3f &uv, Vector3f &normal)
	{
		normal = (hitpoint - center).normalize();
	}
};