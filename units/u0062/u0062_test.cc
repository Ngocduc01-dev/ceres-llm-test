// FILE: u0062_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/sphere_manifold_functions.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ComputeSphereManifoldPlusTest, TC1_SinglePath) {
  using Vec4 = Eigen::Matrix<double, 4, 1>;
  using Vec3 = Eigen::Matrix<double, 3, 1>;

  Vec4 v;
  v << 1.0, 0.2, -0.3, 0.4;
  const double beta = 2.0 / v.squaredNorm();

  double x_data[4] = {0.5, -1.0, 2.0, 1.5};
  double delta_data[3] = {0.3, 0.4, 0.0};
  double out_data[4] = {0.0, 0.0, 0.0, 0.0};

  Eigen::Map<const Vec4> x(x_data);
  Eigen::Map<const Vec3> delta(delta_data);
  Eigen::Map<Vec4> x_plus_delta(out_data);
  const double norm_delta = 0.5;

  ComputeSphereManifoldPlus(v, beta, x, delta, norm_delta, &x_plus_delta);
}

}  // namespace internal
}  // namespace ceres
