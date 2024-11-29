#pragma once

const auto VEC2_H_TEMPLATE { R"(#pragma once

#include "core.h"

namespace be::math {

struct Vec2 {
    real x { 0.0f };
    real y { 0.0f };

    Vec2 operator+(const Vec2 &other) const;
    Vec2 operator-(const Vec2 &other) const;
    Vec2 operator*(real scalar) const;
    Vec2 operator/(real scalar) const;

    Vec2 &operator+=(const Vec2 &other);
    Vec2 &operator-=(const Vec2 &other);
    Vec2 &operator*=(real scalar);
    Vec2 &operator/=(real scalar);

    real dot(const Vec2 &other) const;
    real length() const;
    Vec2 normalized() const;
};

}
)" };

const auto VEC2_CPP_TEMPLATE { R"(#include "be/math/Vec2.h"

#include <math.h>

namespace be::math {

Vec2 Vec2::operator+(const Vec2 &other) const {
    return { x + other.x, y + other.y };
}

Vec2 Vec2::operator-(const Vec2 &other) const {
    return { x - other.x, y - other.y };
}

Vec2 Vec2::operator*(real scalar) const {
    return { x * scalar, y * scalar };
}

Vec2 Vec2::operator/(real scalar) const {
    return { x / scalar, y / scalar };
}

Vec2 &Vec2::operator+=(const Vec2 &other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vec2 &Vec2::operator-=(const Vec2 &other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

Vec2 &Vec2::operator*=(real scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}

Vec2 &Vec2::operator/=(real scalar) {
    x /= scalar;
    y /= scalar;
    return *this;
}

real Vec2::dot(const Vec2 &other) const {
    return x * other.x + y * other.y;
}

real Vec2::length() const {
    return std::sqrt(dot(*this));
}

Vec2 Vec2::normalized() const {
    return *this / length();
}

}
)" };