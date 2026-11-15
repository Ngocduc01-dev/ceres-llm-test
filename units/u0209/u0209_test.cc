// FILE: u0209_test.cc
#include "gtest/gtest.h"
#include "ceres/rotation.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(RotationMatrixToEulerAnglesRowMajorTest, TC1_SinglePath) {
  using System = ceres::internal::EulerSystem<ceres::internal::axis::Z,
                                              ceres::internal::Odd,
                                              ceres::internal::ProperEuler,
                                              ceres::internal::Intrinsic>;
  const double R[9] = {0.7648421873, -0.6442176872, 0.0,
                       0.6442176872, 0.7648421873, 0.0,
                       0.0, 0.0, 1.0};
  double euler[3] = {0.0, 0.0, 0.0};

  ceres::RotationMatrixToEulerAngles<System>(R, euler);
}

}  // namespace internal
}  // namespace ceres
