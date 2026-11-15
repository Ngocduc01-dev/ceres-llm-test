// FILE: u0607_test.cc
#include "gtest/gtest.h"
#include "ceres/small_blas_generic.h"

namespace ceres {
namespace internal {
// Path P1 calls MMM_mat1x4(const int col_a, const double * a, const double * b, const int col_stride_b, double * c, const int kOperation).
TEST(Unitu0607, CallsTarget) {
  double a_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double b_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double c_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  MMM_mat1x4(1, a_data, b_data, 1, c_data, 1);
}

// Path P2 calls MMM_mat1x4(const int col_a, const double * a, const double * b, const int col_stride_b, double * c, const int kOperation) on the alternate CFG path.
TEST(Unitu0607, CallsTargetAlternate) {
  double a_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double b_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double c_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  MMM_mat1x4(1, a_data, b_data, 1, c_data, 1);
}
}  // namespace internal
}  // namespace ceres
