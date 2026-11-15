// FILE: u0056_test.cc
#include <random>

#include "Eigen/Core"
#include "ceres/internal/householder_vector.h"
#include "gtest/gtest.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ApplyHouseholderVectorTest, P1_SingleStraightPath) {
  std::mt19937 gen(42);
  std::uniform_real_distribution<double> dist(-5.0, 5.0);

  Eigen::Matrix<double, 4, 1> y;
  Eigen::Matrix<double, 4, 1> v;
  for (int i = 0; i < 4; ++i) {
    y(i) = dist(gen);
    v(i) = dist(gen);
  }
  const double beta = dist(gen);

  Eigen::Matrix<double, 4, 1> result =
      ApplyHouseholderVector(y, v, beta);
  (void)result;  // Không kiểm tra kết quả trả về.
}

}  // namespace internal
}  // namespace ceres
