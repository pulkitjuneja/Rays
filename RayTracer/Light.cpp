#pragma once

#include "Vector3.cpp"

class Light {
public:
	Vector3f intensity;
	Vector3f position;
	Light(Vector3f intensity, Vector3f position) : intensity(intensity), position(position) {}
};