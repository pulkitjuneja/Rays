#pragma once

#ifndef VECTOR3_H
#define VECTOR3_H

#include "global.h"

template <class T>
class Vector3
{
public:
	T x, y, z;

	Vector3() : x(0), y(0), z(0) {}
	Vector3(T x, T y, T z) : x(x), y(y), z(z) {}
	float lengthSquared() const;
	Vector3(const Vector3 &c);
	Vector3<T> &normalize();
	float dot(Vector3<T> vec) const;
	Vector3<T> operator*(const T &f) const;
	Vector3<T> operator*(const Vector3<T> &v) const;
	Vector3<T> operator+(const Vector3<T> &v);
	Vector3<T> operator-(const Vector3<T> &v) const;
	Vector3<T> operator/(const T &f);
	Vector3<T> operator-();
};

typedef Vector3<float> Vector3f;
typedef Vector3<int> Vector3i;

#endif
