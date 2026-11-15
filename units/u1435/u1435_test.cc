// FILE: u1435_test.cc
#include "gtest/gtest.h"
#include "ceres/block_jacobian_writer.h"
#include "ceres/evaluator.h"
#include "ceres/program.h"

// P1: START -> 1 -> END
TEST(u1435_Test, TC1_CallsTarget) {
  ceres::internal::BlockJacobianWriter target{};
}
