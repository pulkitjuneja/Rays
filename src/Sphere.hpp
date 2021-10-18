#pragma once

#ifndef SPHERE_H
#define SPHERE_H

#include "global.h"
#include "Vector3.cpp"
#include "Renderable.hpp"
#include "Ray.cpp"
#include "HitData.cpp"

class Sphere : public Renderable
{
public:
  float radius;
  Vector3f center;
  Material *material;

  Sphere(Vector3f pos, float rad, Material *mat) : center(pos), radius(rad), material(mat) {}
  virtual bool intersects(Ray &ray, HitData &rec);
  virtual void getSurfaceProperties(Vector3f &hitPoint, Vector3f &normal, Material *&mat);
};

#endif