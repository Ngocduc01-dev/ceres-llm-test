// FILE: u0465_test.cc
#include "gtest/gtest.h"
#include "ceres/conditioned_cost_function.h"
#include "ceres/stl_util.h"

#include <vector>

namespace ceres {
namespace internal {
namespace {

// Cost function giả: 1 residual, 1 khối tham số kích thước 1.
class DummyCostFunction : public CostFunction {
 public:
  DummyCostFunction() {
    set_num_residuals(1);
    mutable_parameter_block_sizes()->push_back(1);
  }
  bool Evaluate(double const* const* parameters,
                double* residuals,
                double** jacobians) const override {
    residuals[0] = parameters[0][0];
    if (jacobians != nullptr && jacobians[0] != nullptr) {
      jacobians[0][0] = 1.0;
    }
    return true;
  }
};

}  // namespace

// P1: START -> 1 -> END (node 1: đúng)
TEST(ConditionedCostFunctionDestructorTest, TakeOwnership) {
  CostFunction* wrapped = new DummyCostFunction();
  std::vector<CostFunction*> conditioners;
  conditioners.push_back(new DummyCostFunction());
  ConditionedCostFunction* cost_function =
      new ConditionedCostFunction(wrapped, conditioners, TAKE_OWNERSHIP);
  delete cost_function;  // gọi destructor một lần
}

// P2: START -> 1 -> 2 -> END (node 1: sai, node 2: release)
TEST(ConditionedCostFunctionDestructorTest, DoNotTakeOwnership) {
  DummyCostFunction wrapped;
  DummyCostFunction conditioner;
  std::vector<CostFunction*> conditioners;
  conditioners.push_back(&conditioner);
  ConditionedCostFunction* cost_function = new ConditionedCostFunction(
      &wrapped, conditioners, DO_NOT_TAKE_OWNERSHIP);
  delete cost_function;  // gọi destructor một lần
}

}  // namespace internal
}  // namespace ceres
