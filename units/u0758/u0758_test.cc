// FILE: u0758_test.cc
#include "gtest/gtest.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0758, TC1_CallsTarget) {
  DenseLinearAlgebraLibraryType type{};
  ceres::IsDenseLinearAlgebraLibraryTypeAvailable(type);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0758, TC2_CallsTarget) {
  DenseLinearAlgebraLibraryType type{};
  ceres::IsDenseLinearAlgebraLibraryTypeAvailable(type);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u0758, TC3_CallsTarget) {
  DenseLinearAlgebraLibraryType type{};
  ceres::IsDenseLinearAlgebraLibraryTypeAvailable(type);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u0758, TC4_CallsTarget) {
  DenseLinearAlgebraLibraryType type{};
  ceres::IsDenseLinearAlgebraLibraryTypeAvailable(type);
}
