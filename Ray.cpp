#pragma once
#include "Vector3.cpp"

class Ray
{
public:
  Vector3f position;
  Vector3f direction;
  Ray() : position(Vector3f(0, 0, 0)),
          direction(Vector3f(0, 0, 0)){};

  Ray(Vector3f position, Vector3f direction) : position(position),
                                               direction(direction){};
  Vector3f pointAtParameter(float t)
  {
    return position + direction * t;
  }
};