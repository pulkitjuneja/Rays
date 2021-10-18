#pragma once

#ifndef SCENE_H
#define SCENE_H

#include "Renderable.hpp"
#include "HitData.cpp"
#include <vector>
#include "Camera.hpp"
#include "RenderOptions.hpp"

using namespace std;

class Scene : public Renderable
{
public:
	vector<Renderable *> sceneObjects;
	Camera camera;

	Scene(RenderOptions &options);
	void add(Renderable *object);
	Camera createCamera(RenderOptions &options);
	void setCamera(Camera camera);
	virtual bool intersects(Ray &ray, HitData &rec);
};

#endif