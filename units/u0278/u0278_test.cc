// FILE: u0278_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_qr.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0278, PathP1) {
  ceres::internal::DenseQR* object = nullptr;
  object->~DenseQR();
}
