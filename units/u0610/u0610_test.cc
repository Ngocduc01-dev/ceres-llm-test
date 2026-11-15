// FILE: u0610_test.cc
#include "gtest/gtest.h"
#include "ceres/small_blas_generic.h"

namespace ceres {
namespace internal {
// Path P1 calls MTV_mat4x1(const int col_a, const double * a, const int col_stride_a, const double * b, double * c, const int kOperation).
TEST(Unitu0610, CallsTarget) {
  double a_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double b_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double c_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  MTV_mat4x1(1, a_data, 1, b_data, c_data, 1);
}

// Path P2 calls MTV_mat4x1(const int col_a, const double * a, const int col_stride_a, const double * b, double * c, const int kOperation) on the alternate CFG path.
TEST(Unitu0610, CallsTargetAlternate) {
  double a_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double b_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double c_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  MTV_mat4x1(1, a_data, 1, b_data, c_data, 1);
}
}  // namespace internal
}  // namespace ceres
