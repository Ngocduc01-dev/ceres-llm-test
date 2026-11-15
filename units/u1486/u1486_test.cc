// FILE: u1486_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"
#include "ceres/map_util.h"
#include "ceres/parameter_block.h"
#include "ceres/problem_impl.h"

// P1: START -> 1 -> END
TEST(u1486_Test, TC1_CallsTarget) {
  ceres::internal::ProblemImpl target{};
  target.SetManifold(nullptr, nullptr);
}
