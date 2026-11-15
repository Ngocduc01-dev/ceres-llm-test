// FILE: u0182_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(EuclideanManifoldRightMultiplyByPlusJacobian, TC1_CopyAmbientToTangent) {
  const int size = 2;
  const int num_rows = 2;
  ceres::EuclideanManifold<ceres::DYNAMIC> manifold(size);

  const double x[2] = {0.3, -0.7};
  const double ambient_matrix[4] = {0.5, -1.2, 2.1, 0.9};
  double tangent_matrix[4] = {0.0, 0.0, 0.0, 0.0};

  manifold.RightMultiplyByPlusJacobian(x, num_rows, ambient_matrix,
                                       tangent_matrix);
}
