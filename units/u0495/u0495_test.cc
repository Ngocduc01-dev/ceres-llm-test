// FILE: u0495_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/autodiff.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0495, PathP1) {
  ceres::internal::Take0thOrderPart<double>(1, nullptr, 0);
}
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0495, PathP2) {
  ceres::internal::Take0thOrderPart<double>(1, nullptr, 0);
}
