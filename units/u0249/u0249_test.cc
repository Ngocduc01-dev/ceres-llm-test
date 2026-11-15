// FILE: u0249_test.cc
#include <random>

#include "gtest/gtest.h"
#include "ceres/callbacks.h"

// Path P1: START -> END (không có điểm rẽ nhánh)
TEST(GradientProblemSolverStateUpdatingCallbackDestructorTest, TC1_P1_DefaultDestructor) {
  std::mt19937 rng(0);
  std::uniform_int_distribution<int> size_dist(1, 5);
  std::uniform_real_distribution<double> value_dist(-10.0, 10.0);

  const int num_parameters = size_dist(rng);
  double internal_parameters[5];
  double user_parameters[5];
  for (int i = 0; i < 5; ++i) {
    internal_parameters[i] = value_dist(rng);
    user_parameters[i] = value_dist(rng);
  }

  // Tạo object trên heap rồi huỷ để gọi destructor đúng một lần.
  auto* callback =
      new ceres::internal::GradientProblemSolverStateUpdatingCallback(
          num_parameters, internal_parameters, user_parameters);
  delete callback;
}
