// FILE: u0712_test.cc
#include "gtest/gtest.h"
#include "ceres/first_order_function.h"
#include "ceres/gradient_problem.h"
#include "ceres/manifold.h"

// Path P1 calls GradientProblem(FirstOrderFunction * function).
TEST(Unitu0712, CallsTarget) {
  double function_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.GradientProblem(function_data);
}
