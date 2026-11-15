// FILE: u0386_test.cc
#include "gtest/gtest.h"
#include "ceres/preconditioner.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(IdentityPreconditionerNumRowsTest, TC1_ReturnNumRows) {
  IdentityPreconditioner preconditioner(3);
  preconditioner.num_rows();
}

}  // namespace internal
}  // namespace ceres
