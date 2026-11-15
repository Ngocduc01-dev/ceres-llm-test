// FILE: u0599_test.cc
#include "gtest/gtest.h"
#include "ceres/problem_impl.h"
#include "ceres/problem_impl.cc"

namespace ceres {
namespace internal {
// Path P1 calls DecrementValueOrDeleteKey(const KeyType key, std::map<KeyType, int>* container).
TEST(Unitu0599, CallsTarget) {
  double container_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  DecrementValueOrDeleteKey({}, container_data);
}
}  // namespace internal
}  // namespace ceres
