#pragma once

const auto MAT3_H_TEMPLATE { R"(#pragma once

#include "core.h"
#include "Vec3.h"

#include <cstddef>

namespace be::math {

class Mat3 {
public:
    Mat3(
        real m00 = 1.0f, real m01 = 0.0f, real m02 = 0.0f,
        real m10 = 0.0f, real m11 = 1.0f, real m12 = 0.0f,
        real m20 = 0.0f, real m21 = 0.0f, real m22 = 1.0f
    );
    ~Mat3();

    Vec3 operator[](std::size_t index);

    real get(std::size_t row, std::size_t column);

    Mat3 operator*(real scalar) const;
    Mat3 &operator*=(real scalar);
    Mat3 operator*(const Mat3 &other) const;
    Vec3 operator*(const Vec3 &vec) const;

    Mat3 makeRotationX(real angle);
    Mat3 makeRotationY(real angle);
    Mat3 makeRotationZ(real angle);
    Mat3 makeRotation(real angle, const Vec3 &axis);
    Mat3 makeUniformScaling(real scale);
    Mat3 makeScale(const Vec3 &direction, real scale);
private:
    real m_values[3][3];
};

}
)" };

const auto MAT3_CPP_TEMPLATE { R"(#include "be/math/Mat3.h"

#include <cmath>

namespace be::math {

Mat3::Mat3(
    real m00, real m01, real m02,
    real m10, real m11, real m12,
    real m20, real m21, real m22
) {
    m_values[0][0] = m00; m_values[0][1] = m01; m_values[0][2] = m02;
    m_values[1][0] = m10; m_values[1][1] = m11; m_values[1][2] = m12;
    m_values[2][0] = m20; m_values[2][1] = m21; m_values[2][2] = m22;
}

Mat3::~Mat3() {}

Vec3 Mat3::operator[](std::size_t index) {
    return Vec3(m_values[0][index], m_values[1][index], m_values[2][index]);
}

real Mat3::get(std::size_t row, std::size_t column) {
    return m_values[row][column];
}

Mat3 Mat3::operator*(real scalar) const {
    return Mat3(
        m_values[0][0] * scalar, m_values[0][1] * scalar, m_values[0][2] * scalar,
        m_values[1][0] * scalar, m_values[1][1] * scalar, m_values[1][2] * scalar,
        m_values[2][0] * scalar, m_values[2][1] * scalar, m_values[2][2] * scalar
    );
}

Mat3 &Mat3::operator*=(real scalar) {
    m_values[0][0] *= scalar; m_values[0][1] *= scalar; m_values[0][2] *= scalar;
    m_values[1][0] *= scalar; m_values[1][1] *= scalar; m_values[1][2] *= scalar;
    m_values[2][0] *= scalar; m_values[2][1] *= scalar; m_values[2][2] *= scalar;

    return *this;
}

Mat3 Mat3::operator*(const Mat3 &other) const {
    return Mat3(
        m_values[0][0] * other.m_values[0][0] + m_values[0][1] * other.m_values[1][0] + m_values[0][2] * other.m_values[2][0],
        m_values[0][0] * other.m_values[0][1] + m_values[0][1] * other.m_values[1][1] + m_values[0][2] * other.m_values[2][1],
        m_values[0][0] * other.m_values[0][2] + m_values[0][1] * other.m_values[1][2] + m_values[0][2] * other.m_values[2][2],
        m_values[1][0] * other.m_values[0][0] + m_values[1][1] * other.m_values[1][0] + m_values[1][2] * other.m_values[2][0],
        m_values[1][0] * other.m_values[0][1] + m_values[1][1] * other.m_values[1][1] + m_values[1][2] * other.m_values[2][1],
        m_values[1][0] * other.m_values[0][2] + m_values[1][1] * other.m_values[1][2] + m_values[1][2] * other.m_values[2][2],
        m_values[2][0] * other.m_values[0][0] + m_values[2][1] * other.m_values[1][0] + m_values[2][2] * other.m_values[2][0],
        m_values[2][0] * other.m_values[0][1] + m_values[2][1] * other.m_values[1][1] + m_values[2][2] * other.m_values[2][1],
        m_values[2][0] * other.m_values[0][2] + m_values[2][1] * other.m_values[1][2] + m_values[2][2] * other.m_values[2][2]
    );
}

Vec3 Mat3::operator*(const Vec3 &vec) const {
    return Vec3(
        m_values[0][0] * vec.x + m_values[0][1] * vec.y + m_values[0][2] * vec.z,
        m_values[1][0] * vec.x + m_values[1][1] * vec.y + m_values[1][2] * vec.z,
        m_values[2][0] * vec.x + m_values[2][1] * vec.y + m_values[2][2] * vec.z
    );
}

Mat3 Mat3::makeRotationX(real angle) {
    real c = std::cos(angle);
    real s = std::sin(angle);

    return Mat3(
        1.0f, 0.0f, 0.0f,
        0.0f, c, -s,
        0.0f, s, c
    );
}

Mat3 Mat3::makeRotationY(real angle) {
    real c = std::cos(angle);
    real s = std::sin(angle);

    return Mat3(
        c, 0.0f, s,
        0.0f, 1.0f, 0.0f,
        -s, 0.0f, c
    );
}

Mat3 Mat3::makeRotationZ(real angle) {
    real c = std::cos(angle);
    real s = std::sin(angle);

    return Mat3(
        c, -s, 0.0f,
        s, c, 0.0f,
        0.0f, 0.0f, 1.0f
    );
}

Mat3 Mat3::makeRotation(real angle, const Vec3 &axis) {
    real c = std::cos(angle);
    real s = std::sin(angle);
    real t = 1.0f - c;

    real x = axis.x;
    real y = axis.y;
    real z = axis.z;

    return Mat3(
        t * x * x + c, t * x * y - s * z, t * x * z + s * y,
        t * x * y + s * z, t * y * y + c, t * y * z - s * x,
        t * x * z - s * y, t * y * z + s * x, t * z * z + c
    );
}

Mat3 Mat3::makeUniformScaling(real scale) {
    return Mat3(
        scale, 0.0f, 0.0f,
        0.0f, scale, 0.0f,
        0.0f, 0.0f, scale
    );
}

Mat3 Mat3::makeScale(const Vec3 &direction, real scale) {
    real km1 = 1.0f - scale;
    real xx = direction.x * direction.x;
    real yy = direction.y * direction.y;
    real zz = direction.z * direction.z;
    real xy = direction.x * direction.y;
    real xz = direction.x * direction.z;
    real yz = direction.y * direction.z;

    return Mat3(
        1 + km1 * xx, km1 * xy, km1 * xz,
        km1 * xy, 1 + km1 * yy, km1 * yz,
        km1 * xz, km1 * yz, 1 + km1 * zz
    );
}

}
)" };
