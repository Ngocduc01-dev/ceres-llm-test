// FILE: u0305_test.cc
#include "gtest/gtest.h"
#include "ceres/gradient_problem.h"
#include "ceres/manifold.h"

namespace ceres {
namespace {

// Hàm mục tiêu đơn giản với 2 tham số, chỉ dùng để dựng GradientProblem.
class SimpleFirstOrderFunction final : public FirstOrderFunction {
 public:
  bool Evaluate(const double* const parameters,
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

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(GradientProblemPlusTest, P1_SingleStatementReturn) {
  GradientProblem problem(new SimpleFirstOrderFunction());

  const double x[2] = {0.7, -1.3};
  const double delta[2] = {0.4, 2.1};
  double x_plus_delta[2] = {0.0, 0.0};

  problem.Plus(x, delta, x_plus_delta);
}

}  // namespace
}  // namespace ceres
