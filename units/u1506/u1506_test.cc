// FILE: u1506_test.cc
#include "gtest/gtest.h"
#include "ceres/trust_region_preprocessor.h"
#include "ceres/ordered_groups.h"
#include "ceres/solver.h"
#include "ceres/coordinate_descent_minimizer.h"
#include "ceres/preprocessor.h"
#include "ceres/problem_impl.h"
#include "ceres/trust_region_preprocessor.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1506, TC1_CallsTarget) {
  ceres::internal::(anonymous)::SetupInnerIterationMinimizer(nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1506, TC2_CallsTarget) {
  ceres::internal::(anonymous)::SetupInnerIterationMinimizer(nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1506, TC3_CallsTarget) {
  ceres::internal::(anonymous)::SetupInnerIterationMinimizer(nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1506, TC4_CallsTarget) {
  ceres::internal::(anonymous)::SetupInnerIterationMinimizer(nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1506, TC5_CallsTarget) {
  ceres::internal::(anonymous)::SetupInnerIterationMinimizer(nullptr);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1506, TC6_CallsTarget) {
  ceres::internal::(anonymous)::SetupInnerIterationMinimizer(nullptr);
}

// P7: START -> 1 -> END; branch decisions covered by case 7
TEST(Unit_u1506, TC7_CallsTarget) {
  ceres::internal::(anonymous)::SetupInnerIterationMinimizer(nullptr);
}
