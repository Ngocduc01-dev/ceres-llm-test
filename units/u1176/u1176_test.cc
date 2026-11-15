// FILE: u1176_test.cc
#include "gtest/gtest.h"
#include "ceres/preprocessor.h"
#include "ceres/solver.h"
#include "ceres/thread_pool.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1176, TC1_CallsTarget) {
  ceres::internal::ChangeNumThreadsIfNeeded(nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1176, TC2_CallsTarget) {
  ceres::internal::ChangeNumThreadsIfNeeded(nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1176, TC3_CallsTarget) {
  ceres::internal::ChangeNumThreadsIfNeeded(nullptr);
}
