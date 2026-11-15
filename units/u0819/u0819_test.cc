// FILE: u0819_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/internal/variadic_evaluate.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0819, TC1_CallsTarget) {
  Functor functor{};
  ceres::internal::VariadicEvaluateImpl(functor, nullptr, nullptr, nullptr);
}
