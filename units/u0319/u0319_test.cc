// FILE: u0319_test.cc
#include "gtest/gtest.h"
#include "ceres/iterative_refiner.h"

namespace ceres {
namespace internal {

// Path P1: START -> END
TEST(DenseIterativeRefinerDestructorTest, DestroyObject) {
  {
    DenseIterativeRefiner refiner(3);
  }  // destructor ~DenseIterativeRefiner() được gọi tại đây
  SUCCEED();
}

}  // namespace internal
}  // namespace ceres
