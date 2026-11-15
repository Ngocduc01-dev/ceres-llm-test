// FILE: u0381_test.cc
#include "gtest/gtest.h"
#include "ceres/preconditioner.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(PreconditionerOptionsConstructorTest, DefaultConstructor_P1) {
  Preconditioner::Options options;
  (void)options;
}

}  // namespace internal
}  // namespace ceres
