// FILE: u0746_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_sparse_matrix.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0746, CallsTarget) {
  double file_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.ToTextFile(file_data);
}
