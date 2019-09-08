#pragma once
#include "renderable.cpp"

class Material;
class Renderable;

struct HitRecord
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