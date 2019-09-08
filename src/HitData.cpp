#pragma once
#include "Renderable.hpp"

class Material;
class Renderable;

struct HitData
{
  Vector3f hitPoint;
  Vector3f normal;
  Material *material;
  Renderable *hitObject;
  float t;
  void calculateProperties(Ray &ray)
  {
    hitPoint = ray.pointAtParameter(t);
    hitObject->getSurfaceProperties(hitPoint, normal, material);
  }
};