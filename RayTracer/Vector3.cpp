#pragma once

#include "global.h"


template <class T>
class Vector3 {
public:
	T x, y, z;
	Vector3() :x(0), y(0), z(0) {}
	Vector3(T x, T y, T z) : x(x), y(y), z(z) {}
	T lengthSquared() {
		return x*x + y*y;
	}

	T length() {
		return sqrt(lengthSquared());
	}
	void normalize() {

	}

};