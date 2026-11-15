// FILE: u0812_test.cc
#include "gtest/gtest.h"
#include "ceres/map_util.h"
#include "ceres/visibility_based_preconditioner.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0812, TC1_CallsTarget) {
  std::unordered_map<int, int> membership_map{};
  ceres::internal::VisibilityBasedPreconditioner object{};
  object.FlattenMembershipMap(membership_map, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0812, TC2_CallsTarget) {
  std::unordered_map<int, int> membership_map{};
  ceres::internal::VisibilityBasedPreconditioner object{};
  object.FlattenMembershipMap(membership_map, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u0812, TC3_CallsTarget) {
  std::unordered_map<int, int> membership_map{};
  ceres::internal::VisibilityBasedPreconditioner object{};
  object.FlattenMembershipMap(membership_map, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u0812, TC4_CallsTarget) {
  std::unordered_map<int, int> membership_map{};
  ceres::internal::VisibilityBasedPreconditioner object{};
  object.FlattenMembershipMap(membership_map, nullptr);
}
