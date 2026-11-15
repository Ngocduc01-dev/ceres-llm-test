// FILE: u0772_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/array_selector.h"
#include "ceres/internal/autodiff.h"
#include "ceres/jet.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0772, TC1_CallsTarget) {
  Functor functor{};
  int dynamic_num_outputs{};
  ceres::internal::AutoDifferentiate(functor, nullptr, dynamic_num_outputs, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0772, TC2_CallsTarget) {
  Functor functor{};
  int dynamic_num_outputs{};
  ceres::internal::AutoDifferentiate(functor, nullptr, dynamic_num_outputs, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u0772, TC3_CallsTarget) {
  Functor functor{};
  int dynamic_num_outputs{};
  ceres::internal::AutoDifferentiate(functor, nullptr, dynamic_num_outputs, nullptr, nullptr);
}
