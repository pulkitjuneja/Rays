#pragma once

#ifndef SCENE_H
#define SCENE_H

#include "Renderable.hpp"
#include "HitData.cpp"
#include <vector>
#include "Camera.hpp"

using namespace std;

class Scene : public Renderable
{
public:
	vector<Renderable *> sceneObjects;
	Camera camera;

	Scene(Camera camera) : sceneObjects(), camera(camera){};
	void add(Renderable *object);
	void setCamera(Camera camera);
	virtual bool intersects(Ray &ray, HitData &rec);
};

#endif