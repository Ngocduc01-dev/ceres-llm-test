// FILE: u1227_test.cc
#include "gtest/gtest.h"
#include "ceres/problem_impl.h"
#include "ceres/context.h"
#include "ceres/casts.h"
#include "ceres/context_impl.h"
#include "ceres/problem_impl.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1227, TC1_CallsTarget) {
  ceres::internal::(anonymous)::InitializeContext(nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1227, TC2_CallsTarget) {
  ceres::internal::(anonymous)::InitializeContext(nullptr, nullptr, nullptr);
}
