// FILE: u0318_test.cc
#include "gtest/gtest.h"
#include "ceres/iterative_refiner.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(DenseIterativeRefinerConstructor, TC1_SinglePath) {
  const int max_num_iterations = 4;
  DenseIterativeRefiner refiner(max_num_iterations);
  (void)refiner;
}

}  // namespace internal
}  // namespace ceres
