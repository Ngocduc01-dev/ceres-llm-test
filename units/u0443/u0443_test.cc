// FILE: u0443_test.cc
#include "gtest/gtest.h"
#include "ceres/dynamic_autodiff_cost_function.h"

namespace ceres {
namespace {

// Functor dùng để khởi tạo DynamicAutoDiffCostFunction (hai khối tham số).
struct DynamicTwoParameterBlockFunctor {
  template <typename T>
  bool operator()(T const* const* parameters, T* residuals) const {
    residuals[0] = parameters[0][0] + parameters[1][0];
    return true;
  }
};

// Path P1: node 1: đúng -> node 2 -> END
TEST(DynamicAutoDiffCostFunctionDestructorTest, DoNotTakeOwnershipReleasesFunctor) {
  DynamicTwoParameterBlockFunctor functor;  // đối tượng trên stack, không được delete
  {
    DynamicAutoDiffCostFunction<DynamicTwoParameterBlockFunctor> cost_function(
        &functor, DO_NOT_TAKE_OWNERSHIP);
  }  // destructor chạy ở đây
  SUCCEED();
}

// Path P2: node 1: sai -> END
TEST(DynamicAutoDiffCostFunctionDestructorTest, TakeOwnershipDeletesFunctor) {
  {
    DynamicAutoDiffCostFunction<DynamicTwoParameterBlockFunctor> cost_function(
        new DynamicTwoParameterBlockFunctor, TAKE_OWNERSHIP);
  }  // destructor chạy ở đây, functor được xoá tự động
  SUCCEED();
}

}  // namespace
}  // namespace ceres
