// FILE: u0468_test.cc
#include "gtest/gtest.h"
#include "ceres/line_search_direction.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> 2 (đúng: num_parameters_ >= 1000) -> 3 -> END
TEST(BFGSConstructorTest, TC1_LargeNumParametersLogsWarning) {
  const int num_parameters = 1024;
  const bool use_approximate_eigenvalue_scaling = true;
  BFGS bfgs(num_parameters, use_approximate_eigenvalue_scaling);
}

// P2: START -> 1 -> 2 (sai: num_parameters_ < 1000) -> 3 -> END
TEST(BFGSConstructorTest, TC2_SmallNumParametersNoWarning) {
  const int num_parameters = 3;
  const bool use_approximate_eigenvalue_scaling = false;
  BFGS bfgs(num_parameters, use_approximate_eigenvalue_scaling);
}

}  // namespace internal
}  // namespace ceres
