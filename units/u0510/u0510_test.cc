// FILE: u0510_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/eigen.h"
#include "ceres/small_blas.h"

namespace ceres {
namespace internal {
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0510, CallsTarget) {
  MatrixMatrixMultiplyEigen({});
}
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0510, CallsTargetAlternate) {
  MatrixMatrixMultiplyEigen({});
}
}  // namespace internal
}  // namespace ceres
