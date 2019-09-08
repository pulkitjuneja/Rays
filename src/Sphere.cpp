#pragma once

#include "global.h"
#include "Vector3.cpp"
#include "renderable.cpp"
#include "Ray.cpp"
#include "HitRecord.cpp"

class Sphere : public Renderable
{
public:
  float radius;
  Vector3f center;
  Material *material;
  Sphere(Vector3f pos, float rad, Material *mat) : center(pos), radius(rad), material(mat) {}

  virtual bool intersects(Ray &ray, HitRecord &rec)
  {
    Vector3f toCenter = center - ray.position;
    float tca = toCenter.dot(ray.direction);
    if (tca < 0)
      return false;
    float d2 = toCenter.lengthSquared() - tca * tca;
    if (d2 > radius * radius)
      return false;
    float thc = sqrt(radius * radius - d2);
    rec.t = tca - thc;
    rec.hitObject = this;
    return true;
  }

  virtual void getSurfaceProperties(Vector3f &hitPoint, Vector3f &normal, Material *&mat)
  {
    normal = (hitPoint - center).normalize();
    mat = this->material;
  }
};