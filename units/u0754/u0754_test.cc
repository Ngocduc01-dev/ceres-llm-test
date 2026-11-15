// FILE: u0754_test.cc
#include "gtest/gtest.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0754, TC1_CallsTarget) {
  DenseLinearAlgebraLibraryType type{};
  ceres::DenseLinearAlgebraLibraryTypeToString(type);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0754, TC2_CallsTarget) {
  DenseLinearAlgebraLibraryType type{};
  ceres::DenseLinearAlgebraLibraryTypeToString(type);
}
