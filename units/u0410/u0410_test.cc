// FILE: u0410_test.cc
#include <random>

#include "ceres/scratch_evaluate_preparer.h"
#include "gtest/gtest.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (hàm không có điểm rẽ nhánh)
TEST(ScratchEvaluatePreparerInitTest, TC1_AllocatesScratchBuffer) {
  // Seed cố định để giá trị luôn giống nhau giữa các lần chạy.
  std::mt19937 rng(12345);
  std::uniform_int_distribution<int> dist(1, 5);
  const int max_derivatives_per_residual_block = dist(rng);

  ScratchEvaluatePreparer obj;
  obj.Init(max_derivatives_per_residual_block);
}

}  // namespace internal
}  // namespace ceres
