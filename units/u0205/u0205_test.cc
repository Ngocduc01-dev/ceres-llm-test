// FILE: u0205_test.cc
#include "gtest/gtest.h"
#include "ceres/rotation.h"

// P1: node 2: đúng
TEST(RotationMatrixToQuaternionTest, TraceNonNegative) {
  // Ma trận cột-chính (column-major), đường chéo: 0.6, 0.5, 0.4
  const double R[9] = {0.6, 0.1, -0.2,
                       0.2, 0.5, 0.3,
                       -0.1, 0.0, 0.4};
  double q[4];
  ceres::RotationMatrixToQuaternion(R, q);
}

// P2: node 2: sai, node 5: sai, node 7: sai
TEST(RotationMatrixToQuaternionTest, NegativeTraceFirstDiagonalLargest) {
  // Đường chéo: -0.2, -0.5, -0.6
  const double R[9] = {-0.2, 0.1, -0.1,
                       0.2, -0.5, 0.3,
                       0.1, -0.3, -0.6};
  double q[4];
  ceres::RotationMatrixToQuaternion(R, q);
}

// P3: node 2: sai, node 5: đúng, node 7: đúng
TEST(RotationMatrixToQuaternionTest, NegativeTraceThirdDiagonalLargest) {
  // Đường chéo: -0.8, -0.5, -0.3
  const double R[9] = {-0.8, 0.2, 0.1,
                       -0.1, -0.5, 0.3,
                       0.2, -0.2, -0.3};
  double q[4];
  ceres::RotationMatrixToQuaternion(R, q);
}
