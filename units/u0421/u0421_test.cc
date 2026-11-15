// FILE: u0421_test.cc
#include "gtest/gtest.h"
#include "ceres/suitesparse.h"

namespace ceres {
namespace internal {

// Path P1: START -> END (hàm không có điểm rẽ nhánh)
TEST(SuiteSparseFreeTest, P1_NoBranch) {
  SuiteSparse obj;
  obj.Free(nullptr);
}

}  // namespace internal
}  // namespace ceres
