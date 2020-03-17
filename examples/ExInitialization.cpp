/**
 * @file    ExInitialization.cpp
 *
 * @author  btran
 *
 * @date    2020-03-17
 *
 * Copyright (c) organization
 *
 */

#include <3d_rotation/3d_rotation.hpp>
#include <cmath>
#include <iostream>

int main(int argc, char* argv[])
{
    rot::Matrix<> m({1, 2, 12, 4, 5, 6, 7, 12, 9}, 3, 3);
    rot::Matrix<> m2({1, 2.2, 3, 4, 5.3, 6, 7, 8.2, 9}, 3, 3);

    double angle = M_PI / 4;
    rot::Quaternion<> q1(0, 0, std::sin(angle), std::cos(angle));
    rot::Quaternion<> q2(0, 0, 1, 0);

    rot::RotationAxisAngle<> r(rot::Vector3D<>({1, 0, 0}), M_PI / 4);
    rot::Vector3D<> origVec({0.4, 5, 3.4});
    auto tmp = r.rotate(origVec);
    std::cout << tmp << "\n";

    rot::RotationQuaternion<> rQ(rot::Vector3D<>({1, 0, 0}), M_PI / 4);
    auto tmp2 = rQ.rotate(origVec);
    std::cout << tmp2 << "\n";

    return 0;
}
