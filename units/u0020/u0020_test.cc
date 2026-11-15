// FILE: u0020_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/dynamic_cost_function_to_functor.h"

namespace {

// CostFunction đơn giản: 1 khối tham số kích thước 1, 1 residual.
class SimpleCostFunction : public ceres::CostFunction {
 public:
  SimpleCostFunction() {
    set_num_residuals(1);
    mutable_parameter_block_sizes()->push_back(1);
  }

  bool Evaluate(double const* const* parameters,
                double* residuals,
                double** jacobians) const override {
    residuals[0] = parameters[0][0];
    if (jacobians != nullptr && jacobians[0] != nullptr) {
      jacobians[0][0] = 1.0;
    }
    return true;
  }
};

}  // namespace

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(DynamicCostFunctionToFunctorTest, TC1_P1_CallEvaluate) {
  // Functor sở hữu cost function (unique_ptr bên trong).
  ceres::DynamicCostFunctionToFunctor functor(new SimpleCostFunction());

  double x = 3.0;
  const double* parameter_blocks[1] = {&x};
  double residuals[1] = {0.0};

  functor(parameter_blocks, residuals);
}
