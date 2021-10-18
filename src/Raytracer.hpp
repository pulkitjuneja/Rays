#pragma once

#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "Vector3.cpp"
#include "global.h"
#include "RenderOptions.hpp"
#include "Material.hpp"
#include "Scene.hpp"
#include <atomic>
#include <thread>

#define PI 3.14159265

using namespace std;

class RayTracer
{
protected:
	int MAX_DEPTH;
	Scene *scene;
	atomic<int> rowsRendered{0};
	atomic<int> nextRow{0};
	Vector3f trace(Ray &ray, int depth);
	template <typename T>
	T clamp(const T &value, const T &low, const T &high)
	{
		return value < low ? low : (value > high ? high : value);
	}

public:
	void render(RenderOptions *options);
	void renderRow(RenderOptions *options, Vector3f *frameBuffer);
	void setScene(Scene *scene);
	void writeToImgae(Vector3f *frameBuffer, RenderOptions *options);
};

#endif