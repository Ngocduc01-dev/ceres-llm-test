// FILE: u1270_test.cc
#include "gtest/gtest.h"
#include "ceres/gradient_problem_solver.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1270, TC1_CallsTarget) {
  ceres::GradientProblemSolver::Summary object{};
  object.FullReport();
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1270, TC2_CallsTarget) {
  ceres::GradientProblemSolver::Summary object{};
  object.FullReport();
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1270, TC3_CallsTarget) {
  ceres::GradientProblemSolver::Summary object{};
  object.FullReport();
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1270, TC4_CallsTarget) {
  ceres::GradientProblemSolver::Summary object{};
  object.FullReport();
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1270, TC5_CallsTarget) {
  ceres::GradientProblemSolver::Summary object{};
  object.FullReport();
}
