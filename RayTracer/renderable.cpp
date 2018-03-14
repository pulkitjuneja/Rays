#pragma once

#include "global.h"
#include "Vector3.cpp"

enum MaterialType
{
	DIFFUSE_AND_GLOSSY,
	REFLECTION_AND_REFRACTION,
	REFLECTION
};

class Material
{
  public:
	float ior, Kd, Ks, specularExponent;
	Vector3f diffuseColor;
	MaterialType type;
	Material(Vector3f dc, float ior, float Kd, float Ks, float specularExponent) : diffuseColor(dc), ior(ior),
																				   Kd(Kd), Ks(Ks), specularExponent(specularExponent) {}
};

class Renderable
{
  public:
	Vector3f center;
	Material surfaceProperties;
	virtual bool intersects(Vector3f &rayOrigin, Vector3f &rayDirection, float &distance) = 0;
	virtual void getProperties(Vector3f &hitpoint, Vector3f &dir, int &index, Vector3f &uv, Vector3f &normal) = 0;
	Renderable(Vector3f pos, Material props) : center(pos), surfaceProperties(props) {}
};