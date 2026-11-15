// FILE: u0805_test.cc
#include "gtest/gtest.h"
#include "ceres/visibility_based_preconditioner.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0805, TC1_CallsTarget) {
  std::vector<std::set<int>> visibility{};
  ceres::internal::VisibilityBasedPreconditioner object{};
  object.ComputeClusterVisibility(visibility, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0805, TC2_CallsTarget) {
  std::vector<std::set<int>> visibility{};
  ceres::internal::VisibilityBasedPreconditioner object{};
  object.ComputeClusterVisibility(visibility, nullptr);
}
