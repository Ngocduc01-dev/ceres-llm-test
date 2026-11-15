// FILE: u1138_test.cc
#include "gtest/gtest.h"
#include "ceres/eigensparse.h"
#include "ceres/suitesparse.h"
#include "ceres/solver.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1138, TC1_CallsTarget) {
  SparseLinearAlgebraLibraryType type{};
  ceres::IsNestedDissectionAvailable(type);
}
