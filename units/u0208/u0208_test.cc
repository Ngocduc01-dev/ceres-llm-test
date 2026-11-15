// FILE: u0208_test.cc
#include <random>

#include "ceres/rotation.h"
#include "gtest/gtest.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(EulerAnglesToRotationRowMajorTest, TC1_P1_YOddTaitBryanIntrinsic) {
  using System = ceres::internal::EulerSystem<ceres::internal::axis::Y,
                                              ceres::internal::Odd,
                                              ceres::internal::TaitBryan,
                                              ceres::internal::Intrinsic>;

  std::mt19937 gen(42);
  std::uniform_real_distribution<double> dist(-1.0, 1.0);

  double euler[3];
  for (int i = 0; i < 3; ++i) {
    euler[i] = dist(gen);
  }
  double R[9] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

  EulerAnglesToRotation<System>(euler, R);
}

}  // namespace internal
}  // namespace ceres
