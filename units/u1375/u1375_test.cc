// FILE: u1375_test.cc
#include "gtest/gtest.h"
#include "ceres/linear_least_squares_problems.h"
#include "ceres/sparse_matrix.h"
#include "ceres/linear_least_squares_problems.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1375, TC1_CallsTarget) {
  std::string filename_base{};
   int{};
  ceres::internal::(anonymous)::DumpLinearLeastSquaresProblemToTextFile(filename_base, nullptr, nullptr, nullptr, nullptr, int);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1375, TC2_CallsTarget) {
  std::string filename_base{};
   int{};
  ceres::internal::(anonymous)::DumpLinearLeastSquaresProblemToTextFile(filename_base, nullptr, nullptr, nullptr, nullptr, int);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1375, TC3_CallsTarget) {
  std::string filename_base{};
   int{};
  ceres::internal::(anonymous)::DumpLinearLeastSquaresProblemToTextFile(filename_base, nullptr, nullptr, nullptr, nullptr, int);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1375, TC4_CallsTarget) {
  std::string filename_base{};
   int{};
  ceres::internal::(anonymous)::DumpLinearLeastSquaresProblemToTextFile(filename_base, nullptr, nullptr, nullptr, nullptr, int);
}
