// FILE: u0890_test.cc
#include "gtest/gtest.h"
#include "ceres/schur_templates.h"
#include "ceres/linear_solver.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0890, TC1_CallsTarget) {
  ceres::internal::GetBestSchurTemplateSpecialization(nullptr, nullptr, nullptr);
}
