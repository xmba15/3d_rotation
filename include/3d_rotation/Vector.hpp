/**
 * @file    Vector.hpp
 *
 * @author  btran
 *
 * @date    2020-03-17
 *
 * Copyright (c) organization
 *
 */

#ifndef VECTOR_HPP_
#define VECTOR_HPP_
#pragma once

#include "Matrix.hpp"
#include <cmath>
#include <cstdint>
#include <vector>

namespace rot
{
template <typename DATA_TYPE = double, std::uint_fast8_t DIMENSION = 3> class Vector : public Matrix<DATA_TYPE>
{
 public:
    using VectorType = Vector<DATA_TYPE, DIMENSION>;
    static_assert(DIMENSION >= 3, "not supported dimension");
    Vector();
    explicit Vector(const std::vector<DATA_TYPE>& data);
    Vector(const Vector<DATA_TYPE, DIMENSION>& other);
    ~Vector() = default;

    DATA_TYPE x() const
    {
        return this->m_data[0];
    }

    DATA_TYPE y() const
    {
        return this->m_data[1];
    }

    DATA_TYPE z() const
    {
        return this->m_data[2];
    }

    DATA_TYPE& x()
    {
        return this->m_data[0];
    }

    DATA_TYPE& y()
    {
        return this->m_data[1];
    }

    DATA_TYPE& z()
    {
        return this->m_data[2];
    }

    VectorType& operator*=(const DATA_TYPE scalar)
    {
        Matrix<DATA_TYPE>::operator*=(scalar);
        return *this;
    }

    VectorType operator*(const DATA_TYPE scalar) const
    {
        VectorType result(*this);
        result *= scalar;
        return result;
    }

    VectorType& operator+=(const VectorType& other)
    {
        Matrix<DATA_TYPE>::operator+=(other);
        return *this;
    }

    VectorType operator+(const VectorType& other) const
    {
        VectorType result(*this);
        result += other;
        return result;
    }

    VectorType& operator-=(const VectorType& other)
    {
        Matrix<DATA_TYPE>::operator-=(other);
        return *this;
    }

    VectorType operator-(const VectorType& other) const
    {
        VectorType result(*this);
        result -= other;
        return result;
    }

    DATA_TYPE operator*(const VectorType& other) const;

    DATA_TYPE l2Norm() const;

    template <typename DATA_TYPE2, std::uint_fast8_t DIMENSION2>
    friend Vector<DATA_TYPE2, DIMENSION2> operator*(const Matrix<DATA_TYPE2>& m,
                                                    const Vector<DATA_TYPE2, DIMENSION2>& v);
};

template <typename DATA_TYPE, std::uint_fast8_t DIMENSION>
Vector<DATA_TYPE, DIMENSION>::Vector() : Matrix<DATA_TYPE>(DIMENSION, 1)
{
}

template <typename DATA_TYPE, std::uint_fast8_t DIMENSION>
Vector<DATA_TYPE, DIMENSION>::Vector(const std::vector<DATA_TYPE>& data) : Matrix<DATA_TYPE>(data, DIMENSION, 1)
{
    assert(data.size() == DIMENSION);
}

template <typename DATA_TYPE, std::uint_fast8_t DIMENSION>
Vector<DATA_TYPE, DIMENSION>::Vector(const Vector<DATA_TYPE, DIMENSION>& other)
    : Vector<DATA_TYPE, DIMENSION>(other.m_data)
{
}

template <typename DATA_TYPE, std::uint_fast8_t DIMENSION>
DATA_TYPE Vector<DATA_TYPE, DIMENSION>::operator*(const VectorType& other) const
{
    DATA_TYPE result = 0;
    for (int i = 0; i < this->size(); ++i) {
        result += this->m_data[i] * other.m_data[i];
    }
    return result;
}

template <typename DATA_TYPE, std::uint_fast8_t DIMENSION> DATA_TYPE Vector<DATA_TYPE, DIMENSION>::l2Norm() const
{
    DATA_TYPE sumSquares = 0;
    for (int i = 0; i < this->size(); ++i) {
        sumSquares += this->m_data[i] * this->m_data[i];
    }

    return std::sqrt(sumSquares);
}

template <typename DATA_TYPE = double> using Vector3D = Vector<DATA_TYPE, 3>;

template <typename DATA_TYPE>
Vector3D<DATA_TYPE> operator^(const Vector3D<DATA_TYPE>& v1, const Vector3D<DATA_TYPE>& v2)
{
    return Vector3D<DATA_TYPE>(
        {v1.y() * v2.z() - v1.z() * v2.y(), v1.z() * v2.x() - v1.x() * v2.z(), v1.x() * v2.y() - v1.y() * v2.x()});
}

template <typename DATA_TYPE, std::uint_fast8_t DIMENSION>
Vector<DATA_TYPE, DIMENSION> operator*(const Matrix<DATA_TYPE>& m, const Vector<DATA_TYPE, DIMENSION>& v)
{
    assert(m.m_col == DIMENSION && m.m_row == DIMENSION);
    auto tmp = m * Matrix<DATA_TYPE>(v.m_data, DIMENSION, 1);

    return Vector<DATA_TYPE, DIMENSION>(tmp.m_data);
}

template <typename DATA_TYPE> Matrix<DATA_TYPE> crossProductMatrix(const Vector3D<DATA_TYPE>& v)
{
    Matrix<DATA_TYPE> m(3, 3);

    // clang-format off
    m(0, 0) = 0; m(0, 1) = -v.z(); m(0, 2) = v.y();
    m(1, 0) = v.z(); m(1, 1) = 0; m(1, 2) = -v.x();
    m(2, 0) = -v.y(); m(2, 1) = v.x(); m(2, 2) = 0;
    // clang-format on

    return m;
}

}  // namespace rot
#endif  // VECTOR_HPP_
