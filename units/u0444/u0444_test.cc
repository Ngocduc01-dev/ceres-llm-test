// FILE: u0444_test.cc
#include "gtest/gtest.h"
#include "ceres/dynamic_numeric_diff_cost_function.h"

namespace {

struct PlusFunctor {
  bool operator()(double const* const* parameters, double* residuals) const {
    residuals[0] = parameters[0][0] + parameters[0][1];
    return true;
  }
};

}  // namespace

// Path P1: node 1: đúng -> node 2 -> END
TEST(DynamicNumericDiffCostFunctionDtorTest, DoNotTakeOwnership) {
  PlusFunctor functor;  // sống trên stack, object không được xoá nó
  {
    ceres::DynamicNumericDiffCostFunction<PlusFunctor, ceres::RIDDERS>
        cost_function(&functor,
                      ceres::DO_NOT_TAKE_OWNERSHIP,
                      ceres::NumericDiffOptions());
  }  // destructor chạy tại đây
}

// Path P2: node 1: sai -> END
TEST(DynamicNumericDiffCostFunctionDtorTest, TakeOwnership) {
  PlusFunctor* functor = new PlusFunctor();  // object sở hữu và tự xoá
  {
    ceres::DynamicNumericDiffCostFunction<PlusFunctor, ceres::RIDDERS>
        cost_function(functor,
                      ceres::TAKE_OWNERSHIP,
                      ceres::NumericDiffOptions());
  }  // destructor chạy tại đây
}
