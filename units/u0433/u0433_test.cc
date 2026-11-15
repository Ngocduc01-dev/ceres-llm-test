// FILE: u0433_test.cc
#include "gtest/gtest.h"
#include "ceres/trust_region_step_evaluator.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(TrustRegionStepEvaluatorConstructorTest, P1_SequentialInitializers) {
  const double initial_cost = 37.5;
  const int max_consecutive_nonmonotonic_steps = 5;
  TrustRegionStepEvaluator evaluator(initial_cost,
                                     max_consecutive_nonmonotonic_steps);
  (void)evaluator;
}

}  // namespace internal
}  // namespace ceres
