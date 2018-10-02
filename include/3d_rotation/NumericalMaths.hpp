/**
 * @file    NumericalMaths.hpp
 *
 * Copyright (c) organization
 *
 */

#ifndef NUMERICALMATHS_HPP_
#define NUMERICALMATHS_HPP_
#pragma once

#include <algorithm>
#include <cmath>
#include <limits>

namespace rot
{
namespace maths
{
template <typename DATA_TYPE>
bool combinedToleranceEquals(const DATA_TYPE val, const DATA_TYPE correctVal,
                             const DATA_TYPE epsilon = std::numeric_limits<DATA_TYPE>::epsilon())
{
    const DATA_TYPE maxXYOne = std::max({static_cast<DATA_TYPE>(1.0f), std::fabs(val), std::fabs(correctVal)});
    return std::fabs(val - correctVal) <= epsilon * maxXYOne;
}
}  // namespace maths
}  // namespace rot

#endif  // NUMERICALMATHS_HPP_
