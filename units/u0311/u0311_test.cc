// FILE: u0311_test.cc
#include "gtest/gtest.h"
#include "ceres/graph.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(WeightedGraphInvalidWeightTest, TC1_StraightPath) {
  WeightedGraph<int> obj;
  obj.InvalidWeight();
}

}  // namespace internal
}  // namespace ceres
