// FILE: u1269_test.cc
#include "gtest/gtest.h"
#include "ceres/problem_impl.h"
#include "ceres/stl_util.h"

// P1: START -> 1 -> END
TEST(u1269_Test, TC1_CallsTarget) {
  ceres::internal::ProblemImpl* target = new ceres::internal::ProblemImpl{};
  target->~ProblemImpl();
}

// P2: START -> 1 -> END
TEST(u1269_Test, TC2_CallsTarget) {
  ceres::internal::ProblemImpl* target = new ceres::internal::ProblemImpl{};
  target->~ProblemImpl();
}

// P3: START -> 1 -> END
TEST(u1269_Test, TC3_CallsTarget) {
  ceres::internal::ProblemImpl* target = new ceres::internal::ProblemImpl{};
  target->~ProblemImpl();
}

// P4: START -> 1 -> END
TEST(u1269_Test, TC4_CallsTarget) {
  ceres::internal::ProblemImpl* target = new ceres::internal::ProblemImpl{};
  target->~ProblemImpl();
}
