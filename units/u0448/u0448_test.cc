// FILE: u0448_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0448, PathP1) {
  { ceres::FixedArray<int, 20> target; }
}
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0448, PathP2) {
  { ceres::FixedArray<int, 20> target; }
}
