// FILE: u0487_test.cc
#include <vector>
#include "gtest/gtest.h"
#include "ceres/stl_util.h"
TEST(Unit_u0487, DeletePointers) {
  std::vector<int*> values;
  ceres::STLDeleteContainerPointers(values.begin(), values.end());
}
