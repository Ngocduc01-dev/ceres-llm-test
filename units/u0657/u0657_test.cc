// FILE: u0657_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_cholesky.h"

// Path P1 calls Factorize(const int num_cols, double * lhs, std::string * message).
TEST(Unitu0657, CallsTarget) {
  double lhs_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double message_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.Factorize(1, lhs_data, message_data);
}
