// FILE: u0488_test.cc
#include <vector>
#include "gtest/gtest.h"
#include "ceres/stl_util.h"
TEST(Unit_u0488, DeleteUniquePointers) {
  std::vector<int*> values;
  ceres::STLDeleteUniqueContainerPointers(values.begin(), values.end());
}
