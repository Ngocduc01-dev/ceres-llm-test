// FILE: u0511_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/eigen.h"
#include "ceres/small_blas.h"

namespace ceres {
namespace internal {
// Path P1 calls MatrixTransposeMatrixMultiplyEigen(xem mã nguồn – hàm được sinh ra từ macro).
TEST(Unitu0511, CallsTarget) {
  MatrixTransposeMatrixMultiplyEigen({});
}
}  // namespace internal
}  // namespace ceres
