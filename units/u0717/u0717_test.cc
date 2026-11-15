// FILE: u0717_test.cc
#include "gtest/gtest.h"
#include "ceres/polynomial.h"

namespace ceres {
namespace internal {
// Path P1 calls EvaluatePolynomial(const Vector & polynomial, double x).
TEST(Unitu0717, CallsTarget) {
  EvaluatePolynomial({}, 1.0);
}
}  // namespace internal
}  // namespace ceres
