/**
 * @file    Rotation.hpp
 *
 * @author  btran
 *
 * @date    2020-03-17
 *
 * Copyright (c) organization
 *
 */

#ifndef ROTATION_HPP_
#define ROTATION_HPP_
#pragma once

#include "Matrix.hpp"
#include "Quaternion.hpp"
#include "Vector.hpp"

namespace rot
{
template <typename DATA_TYPE = double> class RotationBase
{
 public:
    virtual Vector3D<DATA_TYPE> rotate(const Vector3D<DATA_TYPE>& origVec) const = 0;

    static Matrix<DATA_TYPE> RodriguezMatrix(const Vector3D<DATA_TYPE>& unitVec, const DATA_TYPE rotAngle);

 protected:
    RotationBase() = default;
    ~RotationBase() = default;
};

template <typename DATA_TYPE>
Matrix<DATA_TYPE> RotationBase<DATA_TYPE>::RodriguezMatrix(const Vector3D<DATA_TYPE>& unitVec, const DATA_TYPE rotAngle)
{
    auto cpM = crossProductMatrix(unitVec);

    return Matrix<DATA_TYPE>::Identity(3) + cpM * std::sin(rotAngle) + (cpM * cpM) * (1 - std::cos(rotAngle));
}

}  // namespace rot
#endif  //  ROTATION_HPP_
