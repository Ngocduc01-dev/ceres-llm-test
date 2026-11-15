// FILE: u1138_test.cc
#include "gtest/gtest.h"
#include "ceres/eigensparse.h"
#include "ceres/suitesparse.h"
#include "ceres/solver.cc"

// P1: START -> 1 -> END
TEST(IsNestedDissectionAvailableTest, TC1_CallsTarget) {
  SparseLinearAlgebraLibraryType a0{};
  IsNestedDissectionAvailable(a0);
}

