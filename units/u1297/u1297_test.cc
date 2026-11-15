// FILE: u1297_test.cc
#include "gtest/gtest.h"
#include "ceres/reorder_program.h"
#include "ceres/ordered_groups.h"
#include "ceres/parameter_block.h"
#include "ceres/problem_impl.h"
#include "ceres/program.h"

// P1: START -> 1 -> END
TEST(u1297_Test, TC1_CallsTarget) {
  ApplyOrdering(nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1297_Test, TC2_CallsTarget) {
  ApplyOrdering(nullptr, nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1297_Test, TC3_CallsTarget) {
  ApplyOrdering(nullptr, nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1297_Test, TC4_CallsTarget) {
  ApplyOrdering(nullptr, nullptr, nullptr, nullptr);
}
