// FILE: u0384_test.cc
#include "gtest/gtest.h"
#include "ceres/preconditioner.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(IdentityPreconditionerConstructorTest, TC1_P1_ConstructWithNumRows) {
  const int num_rows = 3;  // giá trị chọn trong khoảng [1, 5]
  IdentityPreconditioner preconditioner(num_rows);
  (void)preconditioner;
}

}  // namespace internal
}  // namespace ceres
