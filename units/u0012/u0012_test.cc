// FILE: u0012_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"

namespace ceres {
namespace {

// Lớp con để tạo được object, vì CostFunction có hàm thuần ảo Evaluate.
class DummyCostFunction : public CostFunction {
 public:
  bool Evaluate(double const* const* parameters,
                double* residuals,
                double** jacobians) const override {
    return true;
  }
};

// TC1 - Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(CostFunctionParameterBlockSizesTest, ReturnsParameterBlockSizes) {
  DummyCostFunction cost_function;
  const std::vector<int32_t>& sizes = cost_function.parameter_block_sizes();
  (void)sizes;  // Không kiểm tra kết quả trả về.
}

}  // namespace
}  // namespace ceres
