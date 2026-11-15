// FILE: u0328_test.cc
#include "gtest/gtest.h"
#include "ceres/line_search_minimizer.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(LineSearchMinimizerStateTest, ConstructorTC1) {
  LineSearchMinimizer::State state(4, 3);
}

}  // namespace internal
}  // namespace ceres
