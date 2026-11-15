// FILE: u0415_test.cc
#include "gtest/gtest.h"
#include "ceres/sparse_cholesky.h"

namespace ceres {
namespace internal {

// TC1 - P1: START -> END (không có điểm rẽ nhánh)
TEST(RefinedSparseCholeskyDestructorTest, DestroyObjectWithNullMembers) {
  auto* object = new RefinedSparseCholesky(nullptr, nullptr);
  delete object;  // gọi ~RefinedSparseCholesky() đúng một lần
}

}  // namespace internal
}  // namespace ceres
