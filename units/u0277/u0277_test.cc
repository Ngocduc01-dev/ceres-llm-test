// FILE: u0277_test.cc
#include <memory>
#include <utility>

#include "gtest/gtest.h"
#include "ceres/dense_cholesky.h"

namespace ceres {
namespace internal {

// TC1 - P1: START -> END (hàm không có điểm rẽ nhánh)
TEST(RefinedDenseCholeskyDestructorTest, DestroyObject_P1) {
  std::unique_ptr<DenseCholesky> dense_cholesky(new EigenDenseCholesky());
  std::unique_ptr<DenseIterativeRefiner> refiner(new DenseIterativeRefiner(3));
  {
    RefinedDenseCholesky object(std::move(dense_cholesky), std::move(refiner));
  }  // destructor ~RefinedDenseCholesky() được gọi tại đây
  SUCCEED();
}

}  // namespace internal
}  // namespace ceres
