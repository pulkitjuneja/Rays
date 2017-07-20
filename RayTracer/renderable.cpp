#pragma once 

#include "global.h"
#include "Vector3.cpp"

class SurfaceProperties {
public:
	Vector3f diffuseColor, emmissiveColor;
	float trancparency, reflectance;
	SurfaceProperties(Vector3f dc , Vector3f ec , float transparency, float reflectance) : diffuseColor(dc),
		emmissiveColor(ec), trancparency(transparency), reflectance(reflectance) {}
};

 class Renderable {
 public:
	 Vector3f position;
	 virtual void intersect() = 0;
	 SurfaceProperties surfaceProperties;
	 Renderable(Vector3f pos, SurfaceProperties props) : position(pos), surfaceProperties(props) {}
};