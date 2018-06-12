#pragma once

#include "global.h"
#include "Vector3.cpp"
#include "Ray.cpp"

class Material;
struct HitRecord;

class Renderable
{
public:
  virtual bool intersects(Ray &ray, HitRecord &rec) = 0;
  virtual void getSurfaceProperties(Vector3f &hitPoint, Vector3f &normal, Material *&Material){};
};