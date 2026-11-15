// FILE: u1506_test.cc
#include "gtest/gtest.h"
#include "ceres/trust_region_preprocessor.h"
#include "ceres/ordered_groups.h"
#include "ceres/solver.h"
#include "ceres/coordinate_descent_minimizer.h"
#include "ceres/preprocessor.h"
#include "ceres/problem_impl.h"
#include "ceres/trust_region_preprocessor.cc"

// P1: START -> 1 -> END
TEST(u1506_Test, TC1_CallsTarget) {
  SetupInnerIterationMinimizer(nullptr);
}

// P2: START -> 1 -> END
TEST(u1506_Test, TC2_CallsTarget) {
  SetupInnerIterationMinimizer(nullptr);
}

// P3: START -> 1 -> END
TEST(u1506_Test, TC3_CallsTarget) {
  SetupInnerIterationMinimizer(nullptr);
}

// P4: START -> 1 -> END
TEST(u1506_Test, TC4_CallsTarget) {
  SetupInnerIterationMinimizer(nullptr);
}
