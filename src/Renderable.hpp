#pragma once

#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "global.h"
#include "Vector3.cpp"
#include "Ray.cpp"

class Material;
struct HitData;

class Renderable
{
public:
  virtual bool intersects(Ray &ray, HitData &rec) = 0;
  virtual void getSurfaceProperties(Vector3f &hitPoint, Vector3f &normal, Material *&Material){};
};

#endif