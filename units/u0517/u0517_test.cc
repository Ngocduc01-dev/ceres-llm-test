// FILE: u0517_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/sphere_manifold_functions.h"

namespace ceres {
namespace internal {
// Path P1 calls ComputeSphereManifoldMinus(const VT& v, double beta, const XT& x, const YT& y, YMinusXT* y_minus_x).
TEST(Unitu0517, CallsTarget) {
  double y_minus_x_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  ComputeSphereManifoldMinus({}, 1.0, {}, {}, y_minus_x_data);
}
}  // namespace internal
}  // namespace ceres
