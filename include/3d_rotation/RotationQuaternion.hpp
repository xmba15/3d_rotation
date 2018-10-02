/**
 * @file    RotationQuaternion.hpp
 *
 * @author  btran
 *
 * Copyright (c) organization
 *
 */

#ifndef ROTATIONQUATERNION_HPP_
#define ROTATIONQUATERNION_HPP_
#pragma once

#include "Quaternion.hpp"
#include "RotationBase.hpp"
#include <cmath>

namespace rot
{
template <typename DATA_TYPE = double> class RotationQuaternion : public RotationBase<DATA_TYPE>
{
 public:
    RotationQuaternion(const Vector3D<DATA_TYPE>& unitVec, const DATA_TYPE rotAngle);
    explicit RotationQuaternion(const Quaternion<DATA_TYPE>& unitQ);

    Vector3D<DATA_TYPE> rotate(const Vector3D<DATA_TYPE>& origVec) const override;

 private:
    Quaternion<DATA_TYPE> m_unitQ;
};

template <typename DATA_TYPE>
RotationQuaternion<DATA_TYPE>::RotationQuaternion(const Vector3D<DATA_TYPE>& unitVec, const DATA_TYPE rotAngle)
    : m_unitQ(unitVec * std::sin(rotAngle / 2.), std::cos(rotAngle / 2.), true)
{
}

template <typename DATA_TYPE>
RotationQuaternion<DATA_TYPE>::RotationQuaternion(const Quaternion<DATA_TYPE>& unitQ) : m_unitQ(unitQ, true)
{
}

template <typename DATA_TYPE>
Vector3D<DATA_TYPE> RotationQuaternion<DATA_TYPE>::rotate(const Vector3D<DATA_TYPE>& origVec) const
{
    Quaternion<DATA_TYPE> q(origVec, 0, true);
    return ((this->m_unitQ * q) * (~this->m_unitQ)).v();
}

}  // namespace rot
#endif  // ROTATIONQUATERNION_HPP_
