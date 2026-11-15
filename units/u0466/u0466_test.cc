// FILE: u0466_test.cc
#include "gtest/gtest.h"
#include "ceres/corrector.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0466, PathP1) {
  const int arg_0 = 1;
  double * arg_1 = nullptr;
  ceres::internal::Corrector target(arg_0, arg_1);
  target.CorrectResiduals(1, nullptr);
}
