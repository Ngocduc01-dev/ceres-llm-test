// FILE: u0459_test.cc
#include "gtest/gtest.h"
#include "ceres/rotation.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0459, PathP1) {
  ceres::AngleAxisToQuaternion<double>(nullptr, nullptr);
}
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0459, PathP2) {
  ceres::AngleAxisToQuaternion<double>(nullptr, nullptr);
}
