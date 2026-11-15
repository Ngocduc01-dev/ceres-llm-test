// FILE: u0849_test.cc
#include "gtest/gtest.h"
#include "ceres/dynamic_compressed_row_jacobian_writer.h"
#include "ceres/evaluator.h"
#include "ceres/program.h"

// P1: START -> 1 -> END
TEST(Unit_u0849, TC1_CallsTarget) {
  DynamicCompressedRowJacobianWriter object{};
  Evaluator::Options a0{};
}

