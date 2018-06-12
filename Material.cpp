#pragma once
#include "HitRecord.cpp"
#include "Ray.cpp"
#include "global.h"
#include "Vector3.cpp"

class Material
{
public:
  virtual bool scatter(const Ray &inputRay, HitRecord &rec, Vector3f &attenuation, Ray &outputRay) = 0;
  Vector3f randomInUnitSphere()
  {
    Vector3f unit;
    do
    {
      unit = Vector3f(drand48(), drand48(), drand48()) * 2 - Vector3f(1, 1, 1);
    } while (unit.lengthSquared() >= 1.0f);
    return unit;
  }
};

class Lambertian : public Material
{
  Vector3f albedo;

public:
  Lambertian(Vector3f albedo) : albedo(albedo) {}
  virtual bool scatter(const Ray &inputRay, HitRecord &rec, Vector3f &attenuation, Ray &outputRay)
  {
    Vector3f target = rec.hitPoint + rec.normal + randomInUnitSphere();
    Vector3f direction = (target - rec.hitPoint).normalize();
    outputRay = Ray(rec.hitPoint, direction);
    attenuation = albedo;
    return true;
  }
};

class Metal : public Material
{
  Vector3f albedo;
  float fuzz;

public:
  Metal(Vector3f albedo, float fuzz) : albedo(albedo), fuzz(fuzz) {}
  virtual bool scatter(const Ray &inputRay, HitRecord &rec, Vector3f &attenuation, Ray &outputRay)
  {
    Vector3f reflected = reflect(inputRay.direction, rec.normal) + randomInUnitSphere() * fuzz;
    outputRay = Ray(rec.hitPoint, reflected.normalize());
    attenuation = albedo;
    return (outputRay.direction.dot(rec.normal) > 0);
  }

  Vector3f reflect(const Vector3f &v, const Vector3f &normal)
  {
    return v - normal * 2 * normal.dot(v);
  }
};