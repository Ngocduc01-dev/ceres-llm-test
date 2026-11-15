// FILE: u0401_test.cc
#include <vector>

#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/parameter_block.h"
#include "ceres/residual_block.h"

namespace ceres {
namespace internal {

namespace {

// CostFunction đơn giản: 1 residual, 1 parameter block kích thước 2.
class SimpleCostFunction : public CostFunction {
 public:
  SimpleCostFunction() {
    set_num_residuals(1);
    mutable_parameter_block_sizes()->push_back(2);
  }

  bool Evaluate(double const* const* parameters,
                double* residuals,
                double** jacobians) const override {
    residuals[0] = parameters[0][0] + parameters[0][1];
    if (jacobians != nullptr && jacobians[0] != nullptr) {
      jacobians[0][0] = 1.0;
      jacobians[0][1] = 1.0;
    }
    return true;
  }
};

}  // namespace

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ResidualBlockParameterBlocksTest, TC1_ReturnParameterBlocks) {
  SimpleCostFunction cost_function;
  double x[2] = {1.5, -2.0};
  ParameterBlock parameter_block(x, 2, 0);
  std::vector<ParameterBlock*> parameter_blocks;
  parameter_blocks.push_back(&parameter_block);

  ResidualBlock residual_block(&cost_function, nullptr, parameter_blocks, 0);

  ParameterBlock* const* result = residual_block.parameter_blocks();
  (void)result;  // Không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
