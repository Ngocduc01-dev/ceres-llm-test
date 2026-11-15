// FILE: u0595_test.cc
#include "gtest/gtest.h"
#include "ceres/concurrent_queue.h"

// Path P1 calls PopUnlocked(T * value).
TEST(Unitu0595, CallsTarget) {
  double value_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.PopUnlocked(value_data);
}
