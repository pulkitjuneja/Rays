#pragma once

#include "Vector3.cpp"
#include "global.h"
#include "RenderOptions.cpp"
#include "Material.hpp"
#include "RenderableList.hpp"

#define PI 3.14159265

using namespace std;

class RayTracer
{
protected:
	int MAX_DEPTH;
	RenderableList *scene;
	// vector<Renderable *> sceneObjects;
	Vector3f trace(Ray &ray, int depth);
	template <typename T>
	T clamp(const T &value, const T &low, const T &high)
	{
		return value < low ? low : (value > high ? high : value);
	}

public:
	void render(RenderOptions *options);
	void setScene(RenderableList *scene);
	void writeToImgae(Vector3f *frameBuffer, RenderOptions *options);
	// void addObjectToScene(Renderable *object) { sceneObjects.push_back(object); }
};