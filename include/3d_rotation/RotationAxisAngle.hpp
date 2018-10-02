/**
 * @file    RotationAxisAngle.hpp
 *
 * @author  btran
 *
 * Copyright (c) organization
 *
 */

#ifndef ROTATIONAXISANGLE_HPP_
#define ROTATIONAXISANGLE_HPP_
#pragma once

#include "RotationBase.hpp"

namespace rot
{
template <typename DATA_TYPE = double> class RotationAxisAngle : public RotationBase<DATA_TYPE>
{
 public:
    RotationAxisAngle(const Vector3D<DATA_TYPE>& unitVec, const DATA_TYPE rotAngle);
    ~RotationAxisAngle() = default;

    Vector3D<DATA_TYPE> rotate(const Vector3D<DATA_TYPE>& origVec) const override;

    const Matrix<DATA_TYPE> rotationMatrix;

 private:
    Vector3D<DATA_TYPE> m_unitVec;
    DATA_TYPE m_rotAngle;
};

template <typename DATA_TYPE>
RotationAxisAngle<DATA_TYPE>::RotationAxisAngle(const Vector3D<DATA_TYPE>& unitVec, const DATA_TYPE rotAngle)
    : m_unitVec(unitVec), m_rotAngle(rotAngle),
      rotationMatrix(RotationBase<DATA_TYPE>::RodriguezMatrix(unitVec, rotAngle))
{
}

template <typename DATA_TYPE>
Vector3D<DATA_TYPE> RotationAxisAngle<DATA_TYPE>::rotate(const Vector3D<DATA_TYPE>& origVec) const
{
    return this->rotationMatrix * origVec;
}

}  // namespace rot
#endif  // ROTATIONAXISANGLE_HPP_
