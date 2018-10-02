/**
 * @file    Matrix.hpp
 *
 * @author  btran
 *
 * @date    2020-03-17
 *
 * Copyright (c) organization
 *
 */

#ifndef MATRIX_HPP_
#define MATRIX_HPP_
#pragma once

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <sstream>
#include <string>
#include <vector>

namespace rot
{
template <typename DATA_TYPE, std::uint_fast8_t DIMENSION> class Vector;

template <typename DATA_TYPE = double> class Matrix
{
 public:
    Matrix(const int row, const int col);
    Matrix(const std::vector<DATA_TYPE>& data, const int row, const int col);
    Matrix(const Matrix<DATA_TYPE>& m);

    Matrix<DATA_TYPE>& operator=(const Matrix<DATA_TYPE>& rhs);

    DATA_TYPE operator()(const int i, const int j) const;
    DATA_TYPE& operator()(const int i, const int j);

    static Matrix<DATA_TYPE> Identity(const int n);

    Matrix<DATA_TYPE>& operator*=(const DATA_TYPE scalar);
    Matrix<DATA_TYPE> operator*(const DATA_TYPE scalar) const;

    Matrix<DATA_TYPE> operator*(const Matrix<DATA_TYPE>& other) const;

    Matrix<DATA_TYPE>& operator+=(const Matrix<DATA_TYPE>& other);
    Matrix<DATA_TYPE> operator+(const Matrix<DATA_TYPE>& other) const;

    Matrix<DATA_TYPE>& operator-=(const Matrix<DATA_TYPE>& other);
    Matrix<DATA_TYPE> operator-(const Matrix<DATA_TYPE>& other) const;

    friend std::ostream& operator<<(std::ostream& ss, const Matrix<DATA_TYPE>& m)
    {
        for (int i = 0; i < m.m_row; ++i) {
            for (int j = 0; j < m.m_col; ++j) {
                ss << m(i, j);
                std::string suffix = (j == m.m_col - 1) ? "\n" : " ";
                ss << suffix;
            }
        }
        return ss;
    }

    int size() const;

    template <typename DATA_TYPE2, std::uint_fast8_t DIMENSION>
    friend Vector<DATA_TYPE2, DIMENSION> operator*(const Matrix<DATA_TYPE2>& m, const Vector<DATA_TYPE2, DIMENSION>& v);

 public:
    int m_row;
    int m_col;

 protected:
    std::vector<DATA_TYPE> m_data;
};

template <typename DATA_TYPE> Matrix<DATA_TYPE>::Matrix(const int row, const int col) : m_row(row), m_col(col)
{
    this->m_data = std::vector<DATA_TYPE>(m_row * m_col, (DATA_TYPE)0);
}

template <typename DATA_TYPE>
Matrix<DATA_TYPE>::Matrix(const std::vector<DATA_TYPE>& data, const int row, const int col) : m_row(row), m_col(col)
{
    assert(data.size() == row * col);
    this->m_data = data;
}

template <typename DATA_TYPE>
Matrix<DATA_TYPE>::Matrix(const Matrix<DATA_TYPE>& m) : Matrix<DATA_TYPE>(m.m_data, m.m_row, m.m_col)
{
}

template <typename DATA_TYPE> int Matrix<DATA_TYPE>::size() const
{
    return this->m_row * this->m_col;
}

template <typename DATA_TYPE> Matrix<DATA_TYPE>& Matrix<DATA_TYPE>::operator=(const Matrix<DATA_TYPE>& rhs)
{
    if (this != &rhs) {
        this->m_row = rhs.m_row;
        this->m_col = rhs.m_col;
        this->m_data = rhs.m_data;
    }

    return *this;
}

template <typename DATA_TYPE> DATA_TYPE Matrix<DATA_TYPE>::operator()(const int i, const int j) const
{
    assert(i < m_row && j < m_col);
    return this->m_data[i * m_col + j];
}

template <typename DATA_TYPE> DATA_TYPE& Matrix<DATA_TYPE>::operator()(const int i, const int j)
{
    assert(i < m_row && j < m_col);
    return this->m_data[i * m_col + j];
}

template <typename DATA_TYPE> Matrix<DATA_TYPE> Matrix<DATA_TYPE>::Identity(const int n)
{
    Matrix<DATA_TYPE> result(n, n);

    for (int i = 0; i < n; ++i) {
        result(i, i) = static_cast<DATA_TYPE>(1);
    }

    return result;
}

template <typename DATA_TYPE> Matrix<DATA_TYPE>& Matrix<DATA_TYPE>::operator*=(const DATA_TYPE scalar)
{
    for (auto it = this->m_data.begin(); it != this->m_data.end(); ++it) {
        *it *= scalar;
    }

    return *this;
}

template <typename DATA_TYPE> Matrix<DATA_TYPE> Matrix<DATA_TYPE>::operator*(const DATA_TYPE scalar) const
{
    auto result(*this);
    result *= scalar;
    return result;
}

template <typename DATA_TYPE> Matrix<DATA_TYPE>& Matrix<DATA_TYPE>::operator+=(const Matrix<DATA_TYPE>& other)
{
    assert(this->m_row == other.m_row && this->m_col == other.m_col);
    for (int i = 0; i < this->m_row; ++i) {
        for (int j = 0; j < this->m_col; ++j) {
            this->operator()(i, j) += other(i, j);
        }
    }

    return *this;
}

template <typename DATA_TYPE> Matrix<DATA_TYPE> Matrix<DATA_TYPE>::operator+(const Matrix<DATA_TYPE>& other) const
{
    Matrix<DATA_TYPE> result(*this);
    result += other;

    return result;
}

template <typename DATA_TYPE> Matrix<DATA_TYPE>& Matrix<DATA_TYPE>::operator-=(const Matrix<DATA_TYPE>& other)
{
    assert(this->m_row == other.m_row && this->m_col == other.m_col);

    for (int i = 0; i < this->m_row; ++i) {
        for (int j = 0; j < this->m_col; ++j) {
            this->operator()(i, j) -= other(i, j);
        }
    }

    return *this;
}

template <typename DATA_TYPE> Matrix<DATA_TYPE> Matrix<DATA_TYPE>::operator-(const Matrix<DATA_TYPE>& other) const
{
    Matrix<DATA_TYPE> result(*this);
    result -= other;

    return result;
}

template <typename DATA_TYPE> Matrix<DATA_TYPE> Matrix<DATA_TYPE>::operator*(const Matrix<DATA_TYPE>& other) const
{
    assert(this->m_col == other.m_row);
    Matrix<DATA_TYPE> result(this->m_row, other.m_col);
    for (int i = 0; i < this->m_row; ++i) {
        for (int j = 0; j < other.m_col; ++j) {
            DATA_TYPE sum = 0.0;
            for (int k = 0; k < this->m_col; ++k) {
                sum += this->operator()(i, k) * other(k, j);
            }
            result(i, j) = sum;
        }
    }

    return result;
}

}  // namespace rot
#endif  // MATRIX_HPP_
