// FILE: u1463_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_jacobian_writer.h"
#include "ceres/scratch_evaluate_preparer.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1463, TC1_CallsTarget) {
  int num_threads{};
  ceres::internal::DenseJacobianWriter object{};
  object.CreateEvaluatePreparers(num_threads);
}
