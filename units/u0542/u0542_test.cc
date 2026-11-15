// FILE: u0542_test.cc
#include "gtest/gtest.h"
#include "ceres/small_blas.h"

namespace ceres {
namespace internal {
// Path P1 calls MatrixMatrixMultiply(xem mã nguồn – hàm được sinh ra từ macro).
TEST(Unitu0542, CallsTarget) {
  MatrixMatrixMultiply({});
}
}  // namespace internal
}  // namespace ceres
