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

    Mat2 makeRotation(real angle);
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

Mat2 Mat2::makeRotation(real angle) {
    real c = std::cos(angle);
    real s = std::sin(angle);

    return Mat2(
        c, -s,
        s, c
    );
}

}
)" };
