#pragma once
#include "HitData.cpp"
#include "Ray.cpp"
#include "global.h"
#include "Vector3.cpp"

class Material
{
public:
  virtual bool scatter(const Ray &inputRay, HitData &rec, Vector3f &attenuation, Ray &outputRay) = 0;
  Vector3f randomInUnitSphere();
  Vector3f reflect(const Vector3f &v, const Vector3f &normal);
};

// -------------------------------------------------------------------------------------------------------

class Lambertian : public Material
{
  Vector3f albedo;

public:
  Lambertian(Vector3f albedo) : albedo(albedo) {}
  virtual bool scatter(const Ray &inputRay, HitData &rec, Vector3f &attenuation, Ray &outputRay);
};

// -------------------------------------------------------------------------------------------------------

class Metal : public Material
{
  Vector3f albedo;
  float fuzz;

public:
  Metal(Vector3f albedo, float fuzz) : albedo(albedo), fuzz(fuzz) {}
  virtual bool scatter(const Ray &inputRay, HitData &rec, Vector3f &attenuation, Ray &outputRay);
};

// -------------------------------------------------------------------------------------------------------

class Dielectric : public Material
{
private:
  float refractiveIndex;

public:
  Dielectric(float refractiveIndex) : refractiveIndex(refractiveIndex) {}
  bool refract(const Vector3f &direction, const Vector3f &normal, const float niOverNt, Vector3f refracted);
  float schlick(float cosine, float refractiveIndex);

  virtual bool scatter(const Ray &inputRay, HitData &rec, Vector3f &attenuation, Ray &outputRay);
};