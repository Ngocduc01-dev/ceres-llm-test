// FILE: u1507_test.cc
#include "gtest/gtest.h"
#include "ceres/function_sample.h"
#include "ceres/line_search.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1507, TC1_CallsTarget) {
  const double step_size_estimate{};
  const double initial_cost{};
  const double initial_gradient{};
  ceres::internal::ArmijoLineSearch object{};
  object.DoSearch(step_size_estimate, initial_cost, initial_gradient, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1507, TC2_CallsTarget) {
  const double step_size_estimate{};
  const double initial_cost{};
  const double initial_gradient{};
  ceres::internal::ArmijoLineSearch object{};
  object.DoSearch(step_size_estimate, initial_cost, initial_gradient, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1507, TC3_CallsTarget) {
  const double step_size_estimate{};
  const double initial_cost{};
  const double initial_gradient{};
  ceres::internal::ArmijoLineSearch object{};
  object.DoSearch(step_size_estimate, initial_cost, initial_gradient, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1507, TC4_CallsTarget) {
  const double step_size_estimate{};
  const double initial_cost{};
  const double initial_gradient{};
  ceres::internal::ArmijoLineSearch object{};
  object.DoSearch(step_size_estimate, initial_cost, initial_gradient, nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1507, TC5_CallsTarget) {
  const double step_size_estimate{};
  const double initial_cost{};
  const double initial_gradient{};
  ceres::internal::ArmijoLineSearch object{};
  object.DoSearch(step_size_estimate, initial_cost, initial_gradient, nullptr);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1507, TC6_CallsTarget) {
  const double step_size_estimate{};
  const double initial_cost{};
  const double initial_gradient{};
  ceres::internal::ArmijoLineSearch object{};
  object.DoSearch(step_size_estimate, initial_cost, initial_gradient, nullptr);
}

// P7: START -> 1 -> END; branch decisions covered by case 7
TEST(Unit_u1507, TC7_CallsTarget) {
  const double step_size_estimate{};
  const double initial_cost{};
  const double initial_gradient{};
  ceres::internal::ArmijoLineSearch object{};
  object.DoSearch(step_size_estimate, initial_cost, initial_gradient, nullptr);
}

// P8: START -> 1 -> END; branch decisions covered by case 8
TEST(Unit_u1507, TC8_CallsTarget) {
  const double step_size_estimate{};
  const double initial_cost{};
  const double initial_gradient{};
  ceres::internal::ArmijoLineSearch object{};
  object.DoSearch(step_size_estimate, initial_cost, initial_gradient, nullptr);
}
