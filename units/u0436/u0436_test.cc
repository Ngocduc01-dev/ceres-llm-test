// FILE: u0436_test.cc
#include "gtest/gtest.h"
#include "ceres/autodiff_cost_function.h"

namespace {

// Functor 1 residual, 2 tham số block kích thước 2 và 2.
struct BinaryScalarCost {
  template <typename T>
  bool operator()(const T* x, const T* y, T* residual) const {
    residual[0] = x[0] * y[0] + x[1] * y[1];
    return true;
  }
};

}  // namespace
// Path P1: START -> CFG nodes -> END.
TEST(AutoDiffCostFunctionDestructorTest, DoNotTakeOwnershipReleasesFunctor) {
  BinaryScalarCost functor;  // do test quản lý, không để cost function delete
  auto* cost_function =
      new ceres::AutoDiffCostFunction<BinaryScalarCost, 1, 2, 2>(
          &functor, ceres::DO_NOT_TAKE_OWNERSHIP);
  delete cost_function;  // gọi ~AutoDiffCostFunction()
}
// Path P1: START -> CFG nodes -> END.
TEST(AutoDiffCostFunctionDestructorTest, TakeOwnershipDeletesFunctor) {
  auto* cost_function =
      new ceres::AutoDiffCostFunction<BinaryScalarCost, 1, 2, 2>(
          new BinaryScalarCost, ceres::TAKE_OWNERSHIP);
  delete cost_function;  // gọi ~AutoDiffCostFunction()
}
