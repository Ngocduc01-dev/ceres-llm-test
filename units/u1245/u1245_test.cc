// FILE: u1245_test.cc
#include "gtest/gtest.h"
#include "ceres/gradient_problem_solver.h"

// P1: START -> 1 -> END
TEST(BriefReportTest, TC1_CallsTarget) {
  Summary object{};
  object.BriefReport();
}

