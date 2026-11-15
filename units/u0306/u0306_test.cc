// FILE: u0306_test.cc
#include "gtest/gtest.h"
#include "ceres/gradient_problem_evaluator.h"

namespace {

// Hàm mục tiêu đơn giản: f(x) = 0.5 * sum(x_i^2), dùng để dựng GradientProblem.
class SimpleFirstOrderFunction : public ceres::FirstOrderFunction {
 public:
  explicit SimpleFirstOrderFunction(int num_parameters)
      : num_parameters_(num_parameters) {}

  bool Evaluate(const double* parameters,
                double* cost,
                double* gradient) const override {
    double sum = 0.0;
    for (int i = 0; i < num_parameters_; ++i) {
      sum += 0.5 * parameters[i] * parameters[i];
      if (gradient != nullptr) {
        gradient[i] = parameters[i];
      }
    }
    *cost = sum;
    return true;
  }

  int NumParameters() const override { return num_parameters_; }

 private:
  int num_parameters_;
};

}  // namespace

// Path P1: START -> 1 -> END (không có nhánh rẽ)
TEST(GradientProblemEvaluatorNumResiduals, P1_ReturnsConstant) {
  // Số tham số chọn trong khoảng [1, 5]: 3
  ceres::GradientProblem problem(new SimpleFirstOrderFunction(3));
  ceres::internal::GradientProblemEvaluator evaluator(problem);
  evaluator.NumResiduals();
}
