// FILE: u0316_test.cc
#include "gtest/gtest.h"
#include "ceres/iterative_refiner.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(SparseIterativeRefinerConstructorTest, TC1_P1_ConstructWithMaxNumIterations) {
  const int max_num_iterations = 3;
  SparseIterativeRefiner refiner(max_num_iterations);
  (void)refiner;
}

}  // namespace internal
}  // namespace ceres
