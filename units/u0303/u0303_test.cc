// FILE: u0303_test.cc
#include "gtest/gtest.h"
#include "ceres/first_order_function.h"
#include "ceres/gradient_problem.h"

namespace ceres {
namespace {

// Hàm giả lập chỉ dùng để cung cấp số tham số.
class FakeFirstOrderFunction : public FirstOrderFunction {
 public:
  explicit FakeFirstOrderFunction(int num_parameters)
      : num_parameters_(num_parameters) {}

  bool Evaluate(const double* const parameters,
                double* cost,
                double* gradient) const override {
    cost[0] = 0.0;
    if (gradient != nullptr) {
      for (int i = 0; i < num_parameters_; ++i) {
        gradient[i] = 0.0;
      }
    }
    return true;
  }

  int NumParameters() const override { return num_parameters_; }

 private:
  int num_parameters_;
};

// P1: START -> 1 -> END
TEST(GradientProblemNumParametersTest, TC1_P1_SinglePath) {
  const int kNumParameters = 3;  // khoảng [1, 5], giá trị chọn (seed cố định) = 3
  // GradientProblem nhận quyền sở hữu con trỏ function.
  GradientProblem problem(new FakeFirstOrderFunction(kNumParameters));
  int n = problem.NumParameters();
  (void)n;  // Không kiểm tra kết quả trả về.
}

}  // namespace
}  // namespace ceres
