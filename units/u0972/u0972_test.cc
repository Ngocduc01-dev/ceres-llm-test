// FILE: u0972_test.cc
#include "gtest/gtest.h"
#include "ceres/dogleg_strategy.h"
#include "ceres/sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0972, TC1_CallsTarget) {
  ceres::internal::DoglegStrategy object{};
  object.ComputeSubspaceModel(nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0972, TC2_CallsTarget) {
  ceres::internal::DoglegStrategy object{};
  object.ComputeSubspaceModel(nullptr);
}
