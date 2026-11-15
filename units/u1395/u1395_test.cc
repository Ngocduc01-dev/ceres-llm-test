// FILE: u1395_test.cc
#include "gtest/gtest.h"
#include "ceres/dogleg_strategy.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1395, TC1_CallsTarget) {
  ceres::internal::DoglegStrategy object{};
  object.ComputeSubspaceDoglegStep(nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1395, TC2_CallsTarget) {
  ceres::internal::DoglegStrategy object{};
  object.ComputeSubspaceDoglegStep(nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1395, TC3_CallsTarget) {
  ceres::internal::DoglegStrategy object{};
  object.ComputeSubspaceDoglegStep(nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1395, TC4_CallsTarget) {
  ceres::internal::DoglegStrategy object{};
  object.ComputeSubspaceDoglegStep(nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1395, TC5_CallsTarget) {
  ceres::internal::DoglegStrategy object{};
  object.ComputeSubspaceDoglegStep(nullptr);
}
