// FILE: u0890_test.cc
#include "gtest/gtest.h"
#include "ceres/schur_templates.h"
#include "ceres/linear_solver.h"

// P1: START -> 1 -> END
TEST(GetBestSchurTemplateSpecializationTest, TC1_CallsTarget) {
  int a0[5] = {};
  int a1[5] = {};
  int a2[5] = {};
  ceres::internal::GetBestSchurTemplateSpecialization(a0, a1, a2);
}

