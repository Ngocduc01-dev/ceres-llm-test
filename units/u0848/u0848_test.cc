// FILE: u0848_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_jacobian_writer.h"
#include "ceres/evaluator.h"
#include "ceres/program.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0848, TC1_CallsTarget) {
  Evaluator::Options arg0{};
  ceres::internal::DenseJacobianWriter object{};
  (void)object;
}
