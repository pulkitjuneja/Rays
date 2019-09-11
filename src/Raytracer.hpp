#pragma once

#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "Vector3.cpp"
#include "global.h"
#include "RenderOptions.hpp"
#include "Material.hpp"
#include "Scene.hpp"

#define PI 3.14159265

using namespace std;

class RayTracer
{
protected:
	int MAX_DEPTH;
	Scene *scene;
	Vector3f trace(Ray &ray, int depth);
	template <typename T>
	T clamp(const T &value, const T &low, const T &high)
	{
		return value < low ? low : (value > high ? high : value);
	}

public:
	void render(RenderOptions *options);
	void setScene(Scene *scene);
	void writeToImgae(Vector3f *frameBuffer, RenderOptions *options);
};

#endif