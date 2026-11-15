// FILE: u1463_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_jacobian_writer.h"
#include "ceres/scratch_evaluate_preparer.h"

// P1: START -> 1 -> END
TEST(u1463_Test, TC1_CallsTarget) {
  ceres::internal::DenseJacobianWriter target{};
  target.CreateEvaluatePreparers(nullptr);
}
