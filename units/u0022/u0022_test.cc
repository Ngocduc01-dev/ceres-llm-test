// FILE: u0022_test.cc
#include "gtest/gtest.h"
#include "ceres/first_order_function.h"
#include "ceres/gradient_problem.h"

namespace {

// Hàm mục tiêu đơn giản: f(x) = x0^2 + x1^2, gồm 2 tham số.
class SimpleQuadraticFunction : public ceres::FirstOrderFunction {
 public:
  bool Evaluate(const double* parameters,
                double* cost,
                double* gradient) const override {
    cost[0] = parameters[0] * parameters[0] + parameters[1] * parameters[1];
    if (gradient != nullptr) {
      gradient[0] = 2.0 * parameters[0];
      gradient[1] = 2.0 * parameters[1];
    }
    return true;
  }

  int NumParameters() const override { return 2; }
};

}  // namespace

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(GradientProblemMutableFunctionTest, P1_ReturnFunctionPointer) {
  ceres::GradientProblem problem(new SimpleQuadraticFunction());
  ceres::FirstOrderFunction* function = problem.mutable_function();
  (void)function;  // Không kiểm tra kết quả trả về.
}
