// FILE: u0278_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_qr.h"

TEST(Unit_u0278, PathP1) {
  // Path P1: START -> 1 -> END.
  ceres::internal::DenseQR* object = nullptr;
  object->~DenseQR();
}
