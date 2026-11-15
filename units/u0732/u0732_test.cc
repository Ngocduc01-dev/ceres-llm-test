// FILE: u0732_test.cc
#include "gtest/gtest.h"

namespace ceres {
// Path P1 calls DoglegTypeToString(DoglegType type).
TEST(Unitu0732, CallsTarget) {
  DoglegTypeToString({});
}
}  // namespace ceres
