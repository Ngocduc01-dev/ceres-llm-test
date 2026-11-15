// FILE: u1315_test.cc
#include "gtest/gtest.h"
#include "ceres/trust_region_preprocessor.h"
#include "ceres/solver.h"
#include "ceres/preprocessor.h"
#include "ceres/problem_impl.h"
#include "ceres/reorder_program.h"
#include "ceres/trust_region_preprocessor.cc"

// P1: START -> 1 -> END
TEST(u1315_Test, TC1_CallsTarget) {
  ReorderProgram(nullptr);
}

// P2: START -> 1 -> END
TEST(u1315_Test, TC2_CallsTarget) {
  ReorderProgram(nullptr);
}

// P3: START -> 1 -> END
TEST(u1315_Test, TC3_CallsTarget) {
  ReorderProgram(nullptr);
}

// P4: START -> 1 -> END
TEST(u1315_Test, TC4_CallsTarget) {
  ReorderProgram(nullptr);
}
