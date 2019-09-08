#include "RenderableList.hpp"

void RenderableList::add(Renderable *object)
{
  list.push_back(object);
}

bool RenderableList::intersects(Ray &ray, HitData &rec)
{
  bool hitAnything = false;
  int count = 0;
  float closestSoFar = MAXFLOAT;
  for (vector<Renderable *>::iterator it = list.begin(); it != list.end(); it++)
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