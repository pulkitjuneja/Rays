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

  Vector3f reflect(const Vector3f &v, const Vector3f &normal)
  {
    return v - normal * 2 * normal.dot(v);
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
};

class Dielectric : public Material
{
private:
  float refractiveIndex;

public:
  Dielectric(float refractiveIndex) : refractiveIndex(refractiveIndex) {}
  bool refract(const Vector3f &direction, const Vector3f &normal, const float niOverNt, Vector3f refracted)
  {
    float dot = direction.dot(normal);
    float discriminant = 1 - ((niOverNt * niOverNt) * (1 - dot * dot));
    if (discriminant > 0)
    {
      refracted = (direction - normal * dot) * niOverNt - normal * sqrt(discriminant);
      refracted = refracted.normalize();
      return true;
    }
    else
    {
      return false;
    }
  }

  float schlick(float cosine, float refractiveIndex)
  {
    float r0 = (1 - refractiveIndex) / (1 + refractiveIndex);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
  }

  virtual bool scatter(const Ray &inputRay, HitRecord &rec, Vector3f &attenuation, Ray &outputRay)
  {
    Vector3f outwardNormal;
    float insideOrOutside = inputRay.direction.dot(rec.normal);
    Vector3f refractedDirection(0, 0, 0);
    attenuation = Vector3f(1.0, 1.0, 1.0f);
    Vector3f reflectedDirection = reflect(inputRay.direction, rec.normal);
    float cosine, reflectionProb;
    float niOverNt;
    if (insideOrOutside > 0) // if > 0 means ray is inside of the sphere
    {
      outwardNormal = -rec.normal;
      niOverNt = refractiveIndex;
      float length = inputRay.direction.lengthSquared();
      cosine = inputRay.direction.dot(rec.normal);
      cosine = sqrt(1 - refractiveIndex * refractiveIndex * (1 - cosine * cosine));
    }
    else
    {
      outwardNormal = rec.normal;
      niOverNt = 1.0f / refractiveIndex;
      float length = inputRay.direction.lengthSquared();
      cosine = -(inputRay.direction.dot(rec.normal));
    }
    if (refract(inputRay.direction, outwardNormal, niOverNt, refractedDirection))
    {
      reflectionProb = schlick(cosine, refractiveIndex);
    }
    else
    {
      reflectionProb = 1.0f;
    }
    if (drand48() < reflectionProb)
    {
      outputRay = Ray(rec.hitPoint, refractedDirection);
    }
    else
    {
      outputRay = Ray(rec.hitPoint, reflectedDirection);
    }
    return true;
  }
};