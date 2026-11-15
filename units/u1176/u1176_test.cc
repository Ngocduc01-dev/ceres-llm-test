// FILE: u1176_test.cc
#include "gtest/gtest.h"
#include "ceres/preprocessor.h"
#include "ceres/solver.h"
#include "ceres/thread_pool.h"

// P1: START -> 1 -> END
TEST(ChangeNumThreadsIfNeededTest, TC1_CallsTarget) {
  ceres::internal::ChangeNumThreadsIfNeeded(nullptr);
}

// P2: START -> 1 -> END
TEST(ChangeNumThreadsIfNeededTest, TC2_CallsTarget) {
  ceres::internal::ChangeNumThreadsIfNeeded(nullptr);
}

// P3: START -> 1 -> END
TEST(ChangeNumThreadsIfNeededTest, TC3_CallsTarget) {
  ceres::internal::ChangeNumThreadsIfNeeded(nullptr);
}

