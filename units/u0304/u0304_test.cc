// FILE: u0304_test.cc
#include "gtest/gtest.h"
#include "ceres/gradient_problem.h"
#include "ceres/manifold.h"

namespace ceres {
namespace {

// Hàm mục tiêu đơn giản: f(x) = sum(x_i^2), kích thước cố định 3.
class SquaredSumFunction final : public FirstOrderFunction {
 public:
  bool Evaluate(const double* parameters,
                double* cost,
                double* gradient) const override {
    double sum = 0.0;
    for (int i = 0; i < 3; ++i) {
      sum += parameters[i] * parameters[i];
      if (gradient != nullptr) {
        gradient[i] = 2.0 * parameters[i];
      }
    }
    cost[0] = sum;
    return true;
  }

  int NumParameters() const override { return 3; }
};

// P1: START -> 1 -> END (hàm không có điểm rẽ nhánh)
TEST(GradientProblemNumTangentParameters, P1_ReturnTangentSize) {
  GradientProblem problem(new SquaredSumFunction());
  int tangent_size = problem.NumTangentParameters();
  (void)tangent_size;  // Không kiểm tra kết quả trả về
}

}  // namespace
}  // namespace ceres
