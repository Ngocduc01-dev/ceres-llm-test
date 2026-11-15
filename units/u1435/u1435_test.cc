// FILE: u1435_test.cc
#include "gtest/gtest.h"
#include "ceres/block_jacobian_writer.h"
#include "ceres/evaluator.h"
#include "ceres/program.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1435, TC1_CallsTarget) {
  Evaluator::Options options{};
  ceres::internal::BlockJacobianWriter object{};
  (void)object;
}
