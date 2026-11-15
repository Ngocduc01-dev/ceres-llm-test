// FILE: u0735_test.cc
#include "gtest/gtest.h"

namespace ceres {
// Path P1 calls CovarianceAlgorithmTypeToString(CovarianceAlgorithmType type).
TEST(Unitu0735, CallsTarget) {
  CovarianceAlgorithmTypeToString({});
}
}  // namespace ceres
