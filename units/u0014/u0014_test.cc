// FILE: u0014_test.cc
#include <memory>
#include <random>

#include "ceres/cost_function_to_functor.h"
#include "gtest/gtest.h"

namespace ceres {
namespace {

// CostFunction đơn giản: 1 khối tham số kích thước 2, 2 residual.
class TwoByTwoCostFunction : public CostFunction {
 public:
  TwoByTwoCostFunction() {
    set_num_residuals(2);
    mutable_parameter_block_sizes()->push_back(2);
  }

  bool Evaluate(double const* const* parameters,
                double* residuals,
                double** jacobians) const override {
    residuals[0] = parameters[0][0];
    residuals[1] = parameters[0][1];
    if (jacobians != nullptr && jacobians[0] != nullptr) {
      jacobians[0][0] = 1.0;
      jacobians[0][1] = 0.0;
      jacobians[0][2] = 0.0;
      jacobians[0][3] = 1.0;
    }
    return true;
  }
};

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(CostFunctionToFunctorOperatorTest, TC1_P1_SingleBlockDouble) {
  std::mt19937 gen(42);
  std::uniform_real_distribution<double> dist(-5.0, 5.0);

  double x[2] = {dist(gen), dist(gen)};
  double residuals[2] = {0.0, 0.0};

  CostFunctionToFunctor<2, 2> functor(new TwoByTwoCostFunction());
  functor(x, residuals);
}

}  // namespace
}  // namespace ceres
