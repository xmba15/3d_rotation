/**
 * @file    Quaternion.hpp
 *
 * @author  btran
 *
 * @date    2020-03-17
 *
 * Copyright (c) organization
 *
 */

#ifndef QUATERNION_HPP_
#define QUATERNION_HPP_
#pragma once

#include "NumericalMaths.hpp"
#include "Vector.hpp"
#include <vector>

namespace rot
{
template <typename DATA_TYPE = double> class Quaternion : public Vector<DATA_TYPE, 4>
{
 public:
    using Vector<DATA_TYPE, 4>::Vector;
    explicit Quaternion(const std::vector<DATA_TYPE>& data, const bool isUnit = false);
    Quaternion(const DATA_TYPE x, const DATA_TYPE y, const DATA_TYPE z, const DATA_TYPE w, const bool isUnit = false);
    Quaternion(const Quaternion<DATA_TYPE>& other, const bool isUnit = false);
    Quaternion(const Vector3D<DATA_TYPE>& vec, const DATA_TYPE w, const bool isUnit = false);

    ~Quaternion() = default;

    Vector3D<DATA_TYPE> v() const
    {
        return Vector3D<DATA_TYPE>({this->m_data[0], this->m_data[1], this->m_data[2]});
    }

    DATA_TYPE w() const
    {
        return this->m_data[3];
    }

    DATA_TYPE& w()
    {
        return this->m_data[3];
    }

    Quaternion<DATA_TYPE>& operator*=(const Quaternion<DATA_TYPE>& other);
    Quaternion<DATA_TYPE> operator*(const Quaternion<DATA_TYPE>& other) const;

    Quaternion<DATA_TYPE> operator~() const;

    bool isUnit() const;

 private:
    bool m_isUnit;
    bool approxOne() const;
};

template <typename DATA_TYPE>
Quaternion<DATA_TYPE>::Quaternion(const std::vector<DATA_TYPE>& data, const bool isUnit)
    : Vector<DATA_TYPE, 4>(data), m_isUnit(isUnit)
{
    if (this->m_isUnit && !this->approxOne()) {
        throw std::runtime_error("invalid unit quaternion");
    }
}

template <typename DATA_TYPE>
Quaternion<DATA_TYPE>::Quaternion(const DATA_TYPE x, const DATA_TYPE y, const DATA_TYPE z, const DATA_TYPE w,
                                  const bool isUnit)
    : m_isUnit(isUnit)
{
    this->m_data[0] = x;
    this->m_data[1] = y;
    this->m_data[2] = z;
    this->m_data[3] = w;

    if (this->m_isUnit && !this->approxOne()) {
        throw std::runtime_error("invalid unit quaternion");
    }
}

template <typename DATA_TYPE>
Quaternion<DATA_TYPE>::Quaternion(const Quaternion<DATA_TYPE>& other, const bool isUnit)
    : Quaternion<DATA_TYPE>(other.m_data, isUnit)
{
}

template <typename DATA_TYPE>
Quaternion<DATA_TYPE>::Quaternion(const Vector3D<DATA_TYPE>& vec, const DATA_TYPE w, const bool isUnit)
{
    this->m_data[0] = vec.x();
    this->m_data[1] = vec.y();
    this->m_data[2] = vec.z();
    this->m_data[3] = w;

    if (this->m_isUnit && !this->approxOne()) {
        throw std::runtime_error("invalid unit quaternion");
    }
}

template <typename DATA_TYPE>
Quaternion<DATA_TYPE>& Quaternion<DATA_TYPE>::operator*=(const Quaternion<DATA_TYPE>& other)
{
    Vector3D<DATA_TYPE> q1V = this->v();
    Vector3D<DATA_TYPE> q2V = other.v();

    Vector3D<DATA_TYPE> vectorParts = q2V * this->w() + q1V * other.w() + (q1V ^ q2V);

    this->x() = vectorParts.x();
    this->y() = vectorParts.y();
    this->z() = vectorParts.z();

    this->w() = this->w() * other.w() - q1V * q2V;

    return *this;
}

template <typename DATA_TYPE>
Quaternion<DATA_TYPE> Quaternion<DATA_TYPE>::operator*(const Quaternion<DATA_TYPE>& other) const
{
    Quaternion<DATA_TYPE> result(*this);
    result *= other;
    return result;
}

template <typename DATA_TYPE> Quaternion<DATA_TYPE> Quaternion<DATA_TYPE>::operator~() const
{
    Quaternion<DATA_TYPE> result(*this);
    result.x() *= -1;
    result.y() *= -1;
    result.z() *= -1;
    return result;
}

template <typename DATA_TYPE> bool Quaternion<DATA_TYPE>::isUnit() const
{
    return this->m_isUnit;
}

template <typename DATA_TYPE> bool Quaternion<DATA_TYPE>::approxOne() const
{
    return maths::combinedToleranceEquals(this->l2Norm(), static_cast<DATA_TYPE>(1));
}

}  // namespace rot
#endif  // QUATERNION_HPP_
