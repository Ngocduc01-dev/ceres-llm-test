// FILE: u0741_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/autodiff.h"

// Path P1 calls Apply(const T * src, JetT * dst).
TEST(Unitu0741, CallsTarget) {
  double src_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double dst_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.Apply(src_data, dst_data);
}
