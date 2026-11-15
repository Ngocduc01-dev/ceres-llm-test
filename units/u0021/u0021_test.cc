// FILE: u0021_test.cc
#include "gtest/gtest.h"
#include "ceres/first_order_function.h"
#include "ceres/gradient_problem.h"

namespace ceres {
namespace {

// Hàm một tham số đơn giản, dùng để tạo GradientProblem.
class SimpleFunction final : public FirstOrderFunction {
 public:
  bool Evaluate(const double* parameters,
                double* cost,
                double* gradient) const override {
    cost[0] = parameters[0] * parameters[0];
    if (gradient != nullptr) {
      gradient[0] = 2.0 * parameters[0];
    }
    return true;
  }

  int NumParameters() const override { return 1; }
};

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(GradientProblemFunctionTest, P1_ReturnFunctionPointer) {
  GradientProblem problem(new SimpleFunction());
  const FirstOrderFunction* f = problem.function();
  (void)f;  // Không kiểm tra kết quả trả về.
}

}  // namespace
}  // namespace ceres
