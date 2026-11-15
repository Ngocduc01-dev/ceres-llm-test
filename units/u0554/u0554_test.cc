// FILE: u0554_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/householder_vector.h"

namespace ceres {
namespace internal {
// Path P1 calls ComputeHouseholderVector(const XVectorType& x, Eigen::Matrix<Scalar, N, 1>* v, Scalar* beta).
TEST(Unitu0554, CallsTarget) {
  double v_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double beta_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  ComputeHouseholderVector({}, v_data, beta_data);
}

// Path P2 calls ComputeHouseholderVector(const XVectorType& x, Eigen::Matrix<Scalar, N, 1>* v, Scalar* beta) on the alternate CFG path.
TEST(Unitu0554, CallsTargetAlternate) {
  double v_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double beta_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  ComputeHouseholderVector({}, v_data, beta_data);
}
}  // namespace internal
}  // namespace ceres
