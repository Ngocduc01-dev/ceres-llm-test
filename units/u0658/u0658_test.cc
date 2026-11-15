// FILE: u0658_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_qr.h"

// Path P1 calls Factorize(int num_rows, int num_cols, double * lhs, std::string * message).
TEST(Unitu0658, CallsTarget) {
  double lhs_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double message_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.Factorize(1, 1, lhs_data, message_data);
}
