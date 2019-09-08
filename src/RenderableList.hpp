#pragma once
#include "Renderable.hpp"
#include "HitData.cpp"
#include <vector>

using namespace std;

class RenderableList : public Renderable
{
public:
	vector<Renderable *> list;

	RenderableList() : list() {}
	void add(Renderable *object);
	virtual bool intersects(Ray &ray, HitData &rec);
};