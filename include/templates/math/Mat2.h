#pragma once

const auto MAT2_H_TEMPLATE { R"(#pragma once

#include "core.h"
#include "Vec2.h"

#include <cstddef>

namespace be::math {

class Mat2 {
public:
    Mat2(
        real m00 = 1.0f, real m01 = 0.0f,
        real m10 = 0.0f, real m11 = 1.0f
    );
    ~Mat2();

    Vec2 operator[](std::size_t index);

    real get(std::size_t row, std::size_t column);

    Mat2 operator*(real scalar) const;
    Mat2 &operator*=(real scalar);
    Mat2 operator*(const Mat2 &other) const;
    Vec2 operator*(const Vec2 &vec) const;

    real determinant() const;

    static Mat2 makeRotation(real angle);
    static Mat2 makeUniformScaling(real scale);
    static Mat2 makeScale(const Vec2 &direction, real scale);

    static Mat2 makeOrthoProjX();
    static Mat2 makeOrthoProjY();
    static Mat2 makeOrthoProj(const Vec2 &direction);

    static Mat2 makeReflection(const Vec2 &direction);
private:
    real m_values[2][2];
};

}
)" };

const auto MAT2_CPP_TEMPLATE { R"(#include "be/math/Mat2.h"

#include <cmath>

namespace be::math {

Mat2::Mat2(
    real m00, real m01,
    real m10, real m11
) {
    m_values[0][0] = m00; m_values[0][1] = m01;
    m_values[1][0] = m10; m_values[1][1] = m11;
}

Mat2::~Mat2() {}

Vec2 Mat2::operator[](std::size_t index) {
    return Vec2(m_values[0][index], m_values[1][index]);
}

real Mat2::get(std::size_t row, std::size_t column) {
    return m_values[row][column];
}

Mat2 Mat2::operator*(real scalar) const {
    return Mat2(
        m_values[0][0] * scalar, m_values[0][1] * scalar,
        m_values[1][0] * scalar, m_values[1][1] * scalar
    );
}

Mat2 &Mat2::operator*=(real scalar) {
    m_values[0][0] *= scalar; m_values[0][1] *= scalar;
    m_values[1][0] *= scalar; m_values[1][1] *= scalar;

    return *this;
}

Mat2 Mat2::operator*(const Mat2 &other) const {
    return Mat2(
        m_values[0][0] * other.m_values[0][0] + m_values[0][1] * other.m_values[1][0],
        m_values[0][0] * other.m_values[0][1] + m_values[0][1] * other.m_values[1][1],
        m_values[1][0] * other.m_values[0][0] + m_values[1][1] * other.m_values[1][0],
        m_values[1][0] * other.m_values[0][1] + m_values[1][1] * other.m_values[1][1]
    );
}

Vec2 Mat2::operator*(const Vec2 &vec) const {
    return Vec2(
        m_values[0][0] * vec.x + m_values[0][1] * vec.y,
        m_values[1][0] * vec.x + m_values[1][1] * vec.y
    );
}

real Mat2::determinant() const {
    return m_values[0][0] * m_values[1][1] - m_values[0][1] * m_values[1][0];
}

Mat2 Mat2::makeRotation(real angle) {
    real c = std::cos(angle);
    real s = std::sin(angle);

    return Mat2(
        c, -s,
        s, c
    );
}

Mat2 Mat2::makeUniformScaling(real scale) {
    return Mat2(
        scale, 0.0f,
        0.0f, scale
    );
}

Mat2 Mat2::makeScale(const Vec2 &direction, real scale) {
    real km1 = 1.0f - scale;
    real xx = direction.x * direction.x;
    real yy = direction.y * direction.y;
    real xy = direction.x * direction.y;

    return Mat2(
        1 + km1 * xx, km1 * xy,
        km1 * xy, 1 + km1 * yy
    );
}

Mat2 Mat2::makeOrthoProjX() {
    return Mat2(
        1.0f, 0.0f,
        0.0f, 0.0f
    );
}

Mat2 Mat2::makeOrthoProjY() {
    return Mat2(
        0.0f, 0.0f,
        1.0f, 0.0f
    );
}

Mat2 Mat2::makeOrthoProj(const Vec2 &direction) {
    real x = direction.x;
    real y = direction.y;

    return Mat2(
        1 - x * x, -x * y,
        -x * y, 1 - y * y
    );
}

Mat2 Mat2::makeReflection(const Vec2 &direction) {
    real x = direction.x;
    real y = direction.y;

    return Mat2(
        1 - 2 * x * x, -2 * x * y,
        -2 * x * y, 1 - 2 * y * y
    );
}

}
)" };
