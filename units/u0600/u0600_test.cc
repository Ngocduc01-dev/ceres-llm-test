// FILE: u0600_test.cc
#include "gtest/gtest.h"
#include "ceres/problem_impl.h"
#include "ceres/problem_impl.cc"

namespace ceres {
namespace internal {
// Path P1 calls STLDeleteContainerPairFirstPointers(ForwardIterator begin, ForwardIterator end).
TEST(Unitu0600, CallsTarget) {
  STLDeleteContainerPairFirstPointers({}, {});
}
}  // namespace internal
}  // namespace ceres
