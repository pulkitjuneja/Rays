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

	Vector3<T>& normalize() {
		float length = sqrt(lengthSquared());
		if (length > 0) {
			float invLength = 1 / length;
			x = x*invLength; y = y*invLength; z = z*invLength;
		}
		return *this;
	}
	float dot(Vector3<T> vec) { return x*vec.x + y*vec.y + z*vec.z; }
	Vector3<T> operator * (const T &f) const { return Vec3<T>(x * f, y * f, z * f); }
	Vector3<T> operator * (const Vector3<T> &v) const { return Vec3<T>(x * v.x, y * v.y, z * v.z); }
	Vector3<T> operator + (const Vector3<T> &v) { return Vector<T>(x + v.x, y + v.y, z + v.z); }
	Vector3<T> operator - (const Vector3<T> &v) { return Vector3<T>(x - v.x, y - v.z, z - v.z); }
	Vector3<T> operator - () { return Vector3(-x, -y, -z); }
};

typedef Vector3<float> Vector3f;
typedef Vector3<int> Vector3i;