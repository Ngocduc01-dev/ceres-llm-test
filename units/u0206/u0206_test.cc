// FILE: u0206_test.cc
#include <cmath>

#include "ceres/rotation.h"
#include "gtest/gtest.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(RotationMatrixToAngleAxisColumnMajorTest, SinglePath) {
  const double theta = 0.3;  // giá trị cố định trong (0, pi/2)
  const double c = std::cos(theta);
  const double s = std::sin(theta);

  // Ma trận xoay quanh trục z, lưu theo cột (column-major).
  const double R[9] = {c, s, 0.0, -s, c, 0.0, 0.0, 0.0, 1.0};
  double angle_axis[3] = {0.0, 0.0, 0.0};

  // Không kiểm tra kết quả trả về, chỉ gọi hàm một lần.
  RotationMatrixToAngleAxis<double>(R, angle_axis);
}

}  // namespace internal
}  // namespace ceres
