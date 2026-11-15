// FILE: u0886_test.cc
#include "gtest/gtest.h"
#include "ceres/program_evaluator.h"
#include "ceres/sparse_matrix.h"

// P1: START -> 1 -> END
TEST(operator()Test, TC1_CallsTarget) {
  NullJacobianFinalizer object{};
  i a1{};
  object.operator()(nullptr, a1);
}

