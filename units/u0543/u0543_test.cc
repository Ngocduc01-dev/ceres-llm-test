// FILE: u0543_test.cc
#include "gtest/gtest.h"
#include "ceres/small_blas.h"

namespace ceres {
namespace internal {
// Path P1 calls MatrixTransposeMatrixMultiply(xem mã nguồn – hàm được sinh ra từ macro).
TEST(Unitu0543, CallsTarget) {
  MatrixTransposeMatrixMultiply({});
}
}  // namespace internal
}  // namespace ceres
