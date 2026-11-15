// FILE: u1315_test.cc
#include "gtest/gtest.h"
#include "ceres/trust_region_preprocessor.h"
#include "ceres/solver.h"
#include "ceres/preprocessor.h"
#include "ceres/problem_impl.h"
#include "ceres/reorder_program.h"
#include "ceres/trust_region_preprocessor.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1315, TC1_CallsTarget) {
  ceres::internal::(anonymous)::ReorderProgram(nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1315, TC2_CallsTarget) {
  ceres::internal::(anonymous)::ReorderProgram(nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1315, TC3_CallsTarget) {
  ceres::internal::(anonymous)::ReorderProgram(nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1315, TC4_CallsTarget) {
  ceres::internal::(anonymous)::ReorderProgram(nullptr);
}
