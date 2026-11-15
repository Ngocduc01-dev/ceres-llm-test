// FILE: u0819_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/internal/variadic_evaluate.h"

// P1: START -> 1 -> END
TEST(VariadicEvaluateImplTest, TC1_CallsTarget) {
  Functor& functor a0{};
  ceres::internal::VariadicEvaluateImpl(a0, nullptr, nullptr, nullptr);
}

