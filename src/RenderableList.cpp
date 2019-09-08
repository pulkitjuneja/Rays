#pragma once
#include "renderable.cpp"
#include "HitRecord.cpp"
#include <vector>

using namespace std;

class RenderableList : public Renderable
{
public:
  vector<Renderable *> list;

  RenderableList() : list()
  {
  }

  void add(Renderable *object)
  {
    list.push_back(object);
  }

  virtual bool intersects(Ray &ray, HitRecord &rec)
  {
    bool hitAnything = false;
    int count = 0;
    float closestSoFar = MAXFLOAT;
    for (vector<Renderable *>::iterator it = list.begin(); it != list.end(); it++)
    {
      HitRecord temprec;
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
};