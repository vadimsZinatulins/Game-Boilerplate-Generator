#pragma once

const auto VEC4_H_TEMPLATE { R"(#pragma once

#include "core.h"

namespace be::math {

struct Vec4 {
	real x { 0.0f };
	real y { 0.0f };
	real z { 0.0f };
	real w { 0.0f };

	Vec4 operator+(const Vec4 &other) const;
	Vec4 operator-(const Vec4 &other) const;
	Vec4 operator*(real scalar) const;
	Vec4 operator/(real scalar) const;

	Vec4 &operator+=(const Vec4 &other);
	Vec4 &operator-=(const Vec4 &other);
	Vec4 &operator*=(real scalar);
	Vec4 &operator/=(real scalar);

	real dot(const Vec4 &other) const;
	real length() const;
	Vec4 normalized() const;
};

}
)" };

const auto VEC4_CPP_TEMPLATE { R"(#include "be/math/Vec4.h"

#include <math.h>

namespace be::math {

Vec4 Vec4::operator+(const Vec4 &other) const {
	return { x + other.x, y + other.y, z + other.z, w + other.w };
}

Vec4 Vec4::operator-(const Vec4 &other) const {
	return { x - other.x, y - other.y, z - other.z, w - other.w };
}

Vec4 Vec4::operator*(real scalar) const {
	return { x * scalar, y * scalar, z * scalar, w * scalar };
}

Vec4 Vec4::operator/(real scalar) const {
	return { x / scalar, y / scalar, z / scalar, w / scalar };
}

Vec4 &Vec4::operator+=(const Vec4 &other) {
	x += other.x;
	y += other.y;
	z += other.z;
	w += other.w;
	return *this;
}

Vec4 &Vec4::operator-=(const Vec4 &other) {
	x -= other.x;
	y -= other.y;
	z -= other.z;
	w -= other.w;
	return *this;
}

Vec4 &Vec4::operator*=(real scalar) {
	x *= scalar;
	y *= scalar;
	z *= scalar;
	w *= scalar;
	return *this;
}

Vec4 &Vec4::operator/=(real scalar) {
	x /= scalar;
	y /= scalar;
	z /= scalar;
	w /= scalar;
	return *this;
}

real Vec4::dot(const Vec4 &other) const {
	return x * other.x + y * other.y + z * other.z + w * other.w;
}

real Vec4::length() const {
	return std::sqrt(dot(*this));
}

Vec4 Vec4::normalized() const {
	return *this / length();
}

}
)" };
