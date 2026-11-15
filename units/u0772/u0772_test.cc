// FILE: u0772_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/array_selector.h"
#include "ceres/internal/autodiff.h"
#include "ceres/jet.h"

// P1: START -> 1 -> END
TEST(AutoDifferentiateTest, TC1_CallsTarget) {
  Functor& functor a0{};
  int a2 = 0;
  ceres::internal::AutoDifferentiate(a0, nullptr, a2, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(AutoDifferentiateTest, TC2_CallsTarget) {
  Functor& functor a0{};
  int a2 = 0;
  ceres::internal::AutoDifferentiate(a0, nullptr, a2, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(AutoDifferentiateTest, TC3_CallsTarget) {
  Functor& functor a0{};
  int a2 = 0;
  ceres::internal::AutoDifferentiate(a0, nullptr, a2, nullptr, nullptr);
}

