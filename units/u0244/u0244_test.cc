// FILE: u0244_test.cc
#include "gtest/gtest.h"

namespace {

// Hàm callback giả: ghi nhận số lần được gọi qua user_data, không kiểm tra kết quả.
int FakeCostFunction(void* user_data,
                     double** parameters,
                     double* residuals,
                     double** jacobians) {
  int* counter = static_cast<int*>(user_data);
  ++(*counter);
  residuals[0] = parameters[0][0];
  return 1;
}

}  // namespace

// P1: START -> 1 -> END
TEST(CallbackCostFunctionEvaluate, TC1_SingleStatement) {
  int call_count = 0;
  int parameter_block_sizes[1] = {1};
  ceres::CallbackCostFunction cost_function(
      FakeCostFunction, &call_count, 1, 1, parameter_block_sizes);

  double x = 3.0;
  const double* const parameters[1] = {&x};
  double residuals[1] = {2.0};

  cost_function.Evaluate(parameters, residuals, nullptr);
}
