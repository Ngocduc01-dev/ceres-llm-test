// FILE: u0658_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_qr.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0658, CallsTarget) {
  double lhs_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double message_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.Factorize(1, 1, lhs_data, message_data);
}
