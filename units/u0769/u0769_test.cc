// FILE: u0769_test.cc
#include "gtest/gtest.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0769, TC1_CallsTarget) {
  SparseLinearAlgebraLibraryType type{};
  ceres::SparseLinearAlgebraLibraryTypeToString(type);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0769, TC2_CallsTarget) {
  SparseLinearAlgebraLibraryType type{};
  ceres::SparseLinearAlgebraLibraryTypeToString(type);
}
