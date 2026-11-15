// FILE: u0402_test.cc
#include "gtest/gtest.h"
#include "ceres/residual_block.h"

#include <vector>

namespace ceres {
namespace internal {

namespace {

// CostFunction không có parameter block nào, chỉ dùng để dựng ResidualBlock.
class EmptyCostFunction : public CostFunction {
 public:
  EmptyCostFunction() { set_num_residuals(1); }
  bool Evaluate(double const* const* parameters,
                double* residuals,
                double** jacobians) const override {
    residuals[0] = 0.0;
    return true;
  }
};

}  // namespace

// P1: START -> 1 -> END
TEST(ResidualBlockIndexTest, ReturnsIndex_P1) {
  EmptyCostFunction cost_function;
  std::vector<ParameterBlock*> parameter_blocks;
  const int index = 37;
  ResidualBlock residual_block(
      &cost_function, nullptr, parameter_blocks, index);
  residual_block.index();
}

}  // namespace internal
}  // namespace ceres
