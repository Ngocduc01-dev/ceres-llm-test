// FILE: u0495_test.cc
#include "gtest/gtest.h"
TEST(Unit_u0495, Take0thOrderPart) {
  ceres::Jet<double, 2> source[1] = {ceres::Jet<double, 2>(1.0)};
  double destination = 0.0;
  ceres::internal::Take0thOrderPart(1, source, destination);
}
