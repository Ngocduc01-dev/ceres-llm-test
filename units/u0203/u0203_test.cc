// FILE: u0203_test.cc
#include "gtest/gtest.h"
#include "ceres/rotation.h"

namespace ceres {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(MatrixAdapterConstructorTest, P1_ConstructFromPointer) {
  const double data[3] = {2.0, -7.0, 5.0};
  MatrixAdapter<const double, 1, 3> adapter(data);
  (void)adapter;
}

}  // namespace ceres
