#pragma once

const auto VEC3_H_TEMPLATE { R"(#pragma once

#include "core.h"

namespace be::math {

struct Vec3 {
    real x { 0.0f };
    real y { 0.0f };
    real z { 0.0f };

    Vec3 operator+(const Vec3 &other) const;
    Vec3 operator-(const Vec3 &other) const;
    Vec3 operator*(real scalar) const;
    Vec3 operator/(real scalar) const;

    Vec3 &operator+=(const Vec3 &other);
    Vec3 &operator-=(const Vec3 &other);
    Vec3 &operator*=(real scalar);
    Vec3 &operator/=(real scalar);

    real dot(const Vec3 &other) const;
    Vec3 cross(const Vec3 &other) const;
    real length() const;
    Vec3 normalized() const;
};

}
)" };

const auto VEC3_CPP_TEMPLATE { R"(#include "be/math/Vec3.h"

#include <math.h>

namespace be::math {
    
Vec3 Vec3::operator+(const Vec3 &other) const {
    return { x + other.x, y + other.y, z + other.z };
}

Vec3 Vec3::operator-(const Vec3 &other) const {
    return { x - other.x, y - other.y, z - other.z };
}

Vec3 Vec3::operator*(real scalar) const {
    return { x * scalar, y * scalar, z * scalar };
}

Vec3 Vec3::operator/(real scalar) const {
    return { x / scalar, y / scalar, z / scalar };
}

Vec3 &Vec3::operator+=(const Vec3 &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vec3 &Vec3::operator-=(const Vec3 &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Vec3 &Vec3::operator*=(real scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

Vec3 &Vec3::operator/=(real scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}

real Vec3::dot(const Vec3 &other) const {
    return x * other.x + y * other.y + z * other.z;
}

Vec3 Vec3::cross(const Vec3 &other) const {
    return { y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x };
}

real Vec3::length() const {
    return std::sqrt(dot(*this));
}

Vec3 Vec3::normalized() const {
    return *this / length();
}

}
)" };
