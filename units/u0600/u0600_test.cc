// FILE: u0600_test.cc
#include "gtest/gtest.h"
#include "ceres/problem_impl.h"
#include "ceres/problem_impl.cc"
#include <map>

namespace ceres {
namespace internal {
// Path P1: START -> 1 -> 2 -> 1 -> END.
TEST(Unit_u0600, PathP1) {
  std::map<CostFunction*, int> items;
  items.emplace(nullptr, 1);
  STLDeleteContainerPairFirstPointers(items.begin(), items.end());
}
}  // namespace internal
}  // namespace ceres
