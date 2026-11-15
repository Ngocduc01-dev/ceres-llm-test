// FILE: u0972_test.cc
#include "gtest/gtest.h"
#include "ceres/dogleg_strategy.h"
#include "ceres/sparse_matrix.h"

// P1: START -> 1 -> END
TEST(ComputeSubspaceModelTest, TC1_CallsTarget) {
  DoglegStrategy object{};
  object.ComputeSubspaceModel(nullptr);
}

// P2: START -> 1 -> END
TEST(ComputeSubspaceModelTest, TC2_CallsTarget) {
  DoglegStrategy object{};
  object.ComputeSubspaceModel(nullptr);
}

