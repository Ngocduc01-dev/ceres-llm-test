// FILE: u1438_test.cc
#include "gtest/gtest.h"
#include "ceres/linear_least_squares_problems.h"
#include "ceres/sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1438, TC1_CallsTarget) {
  std::string filename_base{};
  DumpFormatType dump_format_type{};
  int num_eliminate_blocks{};
  ceres::internal::DumpLinearLeastSquaresProblem(filename_base, dump_format_type, nullptr, nullptr, nullptr, nullptr, num_eliminate_blocks);
}
