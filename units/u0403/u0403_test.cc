// FILE: u0403_test.cc
#include "gtest/gtest.h"
#include "ceres/residual_block.h"

#include <vector>

namespace ceres {
namespace internal {

namespace {

// CostFunction đơn giản: 0 parameter block, 1 residual.
class DummyCostFunction : public CostFunction {
 public:
  DummyCostFunction() { set_num_residuals(1); }
  bool Evaluate(double const* const* parameters,
                double* residuals,
                double** jacobians) const override {
    residuals[0] = 0.0;
    return true;
  }
};

}  // namespace

// Path P1: START -> 1 -> END
TEST(ResidualBlockSetIndexTest, TC1_P1_SetIndex) {
  DummyCostFunction cost_function;
  std::vector<ParameterBlock*> parameter_blocks;
  ResidualBlock residual_block(&cost_function, nullptr, parameter_blocks, 0);

  residual_block.set_index(3);
}

}  // namespace internal
}  // namespace ceres
