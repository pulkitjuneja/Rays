#include "Scene.hpp"

void Scene::add(Renderable *object)
{
  sceneObjects.push_back(object);
}

bool Scene::intersects(Ray &ray, HitData &rec)
{
  bool hitAnything = false;
  int count = 0;
  float closestSoFar = MAXFLOAT;
  for (vector<Renderable *>::iterator it = sceneObjects.begin(); it != sceneObjects.end(); it++)
  {
    HitData temprec;
    if ((*it)->intersects(ray, temprec))
    {
      if (temprec.t < closestSoFar)
      {
        closestSoFar = temprec.t;
        rec = temprec;
        hitAnything = true;
      }
    }
  }
  return hitAnything;
}