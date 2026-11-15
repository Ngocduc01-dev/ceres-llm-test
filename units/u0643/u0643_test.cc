// FILE: u0643_test.cc
#include "gtest/gtest.h"
#include "ceres/rotation.h"

namespace ceres {
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0643, CallsTarget) {
  double pointer_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  RowMajorAdapter3x3(pointer_data);
}
}  // namespace ceres
