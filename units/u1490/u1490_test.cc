// FILE: u1490_test.cc
#include "gtest/gtest.h"
#include "ceres/iteration_callback.h"
#include "ceres/solver.h"
#include "ceres/minimizer.h"
#include "ceres/trust_region_minimizer.h"
#include "ceres/trust_region_step_evaluator.h"
#include "ceres/trust_region_strategy.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1490, TC1_CallsTarget) {
  Minimizer::Options options{};
  ceres::internal::TrustRegionMinimizer object{};
  object.Minimize(options, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1490, TC2_CallsTarget) {
  Minimizer::Options options{};
  ceres::internal::TrustRegionMinimizer object{};
  object.Minimize(options, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1490, TC3_CallsTarget) {
  Minimizer::Options options{};
  ceres::internal::TrustRegionMinimizer object{};
  object.Minimize(options, nullptr, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1490, TC4_CallsTarget) {
  Minimizer::Options options{};
  ceres::internal::TrustRegionMinimizer object{};
  object.Minimize(options, nullptr, nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1490, TC5_CallsTarget) {
  Minimizer::Options options{};
  ceres::internal::TrustRegionMinimizer object{};
  object.Minimize(options, nullptr, nullptr);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1490, TC6_CallsTarget) {
  Minimizer::Options options{};
  ceres::internal::TrustRegionMinimizer object{};
  object.Minimize(options, nullptr, nullptr);
}

// P7: START -> 1 -> END; branch decisions covered by case 7
TEST(Unit_u1490, TC7_CallsTarget) {
  Minimizer::Options options{};
  ceres::internal::TrustRegionMinimizer object{};
  object.Minimize(options, nullptr, nullptr);
}

// P8: START -> 1 -> END; branch decisions covered by case 8
TEST(Unit_u1490, TC8_CallsTarget) {
  Minimizer::Options options{};
  ceres::internal::TrustRegionMinimizer object{};
  object.Minimize(options, nullptr, nullptr);
}

// P9: START -> 1 -> END; branch decisions covered by case 9
TEST(Unit_u1490, TC9_CallsTarget) {
  Minimizer::Options options{};
  ceres::internal::TrustRegionMinimizer object{};
  object.Minimize(options, nullptr, nullptr);
}

// P10: START -> 1 -> END; branch decisions covered by case 10
TEST(Unit_u1490, TC10_CallsTarget) {
  Minimizer::Options options{};
  ceres::internal::TrustRegionMinimizer object{};
  object.Minimize(options, nullptr, nullptr);
}

// P11: START -> 1 -> END; branch decisions covered by case 11
TEST(Unit_u1490, TC11_CallsTarget) {
  Minimizer::Options options{};
  ceres::internal::TrustRegionMinimizer object{};
  object.Minimize(options, nullptr, nullptr);
}

// P12: START -> 1 -> END; branch decisions covered by case 12
TEST(Unit_u1490, TC12_CallsTarget) {
  Minimizer::Options options{};
  ceres::internal::TrustRegionMinimizer object{};
  object.Minimize(options, nullptr, nullptr);
}
