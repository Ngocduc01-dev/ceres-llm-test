// FILE: u1234_test.cc
#include "gtest/gtest.h"
#include "ceres/evaluator.h"
#include "ceres/sparse_matrix.h"
#include "ceres/trust_region_minimizer.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1234, TC1_CallsTarget) {
  bool new_evaluation_point{};
  ceres::internal::TrustRegionMinimizer object{};
  object.EvaluateGradientAndJacobian(new_evaluation_point);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1234, TC2_CallsTarget) {
  bool new_evaluation_point{};
  ceres::internal::TrustRegionMinimizer object{};
  object.EvaluateGradientAndJacobian(new_evaluation_point);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1234, TC3_CallsTarget) {
  bool new_evaluation_point{};
  ceres::internal::TrustRegionMinimizer object{};
  object.EvaluateGradientAndJacobian(new_evaluation_point);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1234, TC4_CallsTarget) {
  bool new_evaluation_point{};
  ceres::internal::TrustRegionMinimizer object{};
  object.EvaluateGradientAndJacobian(new_evaluation_point);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1234, TC5_CallsTarget) {
  bool new_evaluation_point{};
  ceres::internal::TrustRegionMinimizer object{};
  object.EvaluateGradientAndJacobian(new_evaluation_point);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1234, TC6_CallsTarget) {
  bool new_evaluation_point{};
  ceres::internal::TrustRegionMinimizer object{};
  object.EvaluateGradientAndJacobian(new_evaluation_point);
}
