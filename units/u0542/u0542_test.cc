// FILE: u0542_test.cc
#include "gtest/gtest.h"
#include "ceres/small_blas.h"

namespace ceres {
namespace internal {
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0542, CallsTarget) {
  MatrixMatrixMultiply({});
}
}  // namespace internal
}  // namespace ceres
