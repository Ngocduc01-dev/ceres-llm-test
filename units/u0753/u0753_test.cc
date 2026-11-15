// FILE: u0753_test.cc
#include "gtest/gtest.h"
#include "ceres/preconditioner.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0753, TC1_CallsTarget) {
  PreconditionerType preconditioner_type{};
  ceres::internal::Preconditioner object{};
  object.PreconditionerForZeroEBlocks(preconditioner_type);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0753, TC2_CallsTarget) {
  PreconditionerType preconditioner_type{};
  ceres::internal::Preconditioner object{};
  object.PreconditionerForZeroEBlocks(preconditioner_type);
}
