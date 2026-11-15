// FILE: u0510_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/eigen.h"
#include "ceres/small_blas.h"

namespace ceres {
namespace internal {
// Path P1 calls MatrixMatrixMultiplyEigen(xem mã nguồn – hàm được sinh ra từ macro).
TEST(Unitu0510, CallsTarget) {
  MatrixMatrixMultiplyEigen({});
}

// Path P2 calls MatrixMatrixMultiplyEigen(xem mã nguồn – hàm được sinh ra từ macro) on the alternate CFG path.
TEST(Unitu0510, CallsTargetAlternate) {
  MatrixMatrixMultiplyEigen({});
}
}  // namespace internal
}  // namespace ceres
