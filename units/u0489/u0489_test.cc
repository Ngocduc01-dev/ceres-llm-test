// FILE: u0489_test.cc
#include <vector>
#include "gtest/gtest.h"
#include "ceres/stl_util.h"
TEST(Unit_u0489, DeleteElements) { std::vector<int*> values; ceres::STLDeleteElements(&values); }
