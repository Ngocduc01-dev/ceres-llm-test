// FILE: u0317_test.cc
#include "gtest/gtest.h"
#include "ceres/iterative_refiner.h"

namespace ceres {
namespace internal {

// Path P1: START -> END (destructor mặc định, không có nhánh)
TEST(SparseIterativeRefinerDestructorTest, DestroyObject) {
  {
    SparseIterativeRefiner refiner(3);
  }  // destructor ~SparseIterativeRefiner() được gọi ở đây
  SUCCEED();
}

}  // namespace internal
}  // namespace ceres
