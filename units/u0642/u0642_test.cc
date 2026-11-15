// FILE: u0642_test.cc
#include "gtest/gtest.h"
#include "ceres/rotation.h"

namespace ceres {
// Path P1 calls ColumnMajorAdapter3x3(T* pointer).
TEST(Unitu0642, CallsTarget) {
  double pointer_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  ColumnMajorAdapter3x3(pointer_data);
}
}  // namespace ceres
