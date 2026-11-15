// FILE: u0456_test.cc
#include "gtest/gtest.h"
#include "ceres/numeric_diff_first_order_function.h"

namespace ceres {
namespace {

// Functor 4 tham số, trả về cost = tổng bình phương các tham số.
struct QuadraticCostFunctor {
  bool operator()(const double* parameters, double* cost) const {
    double sum = 0.0;
    for (int i = 0; i < 4; ++i) {
      sum += parameters[i] * parameters[i];
    }
    *cost = sum;
    return true;
  }
};

// P1: node 1: đúng (ownership_ != TAKE_OWNERSHIP) -> node 2 -> END
TEST(NumericDiffFirstOrderFunctionDtorTest, DoNotTakeOwnership) {
  QuadraticCostFunctor functor;  // sống trên stack, destructor không được delete
  {
    NumericDiffFirstOrderFunction<QuadraticCostFunctor, CENTRAL, 4> function(
        &functor, DO_NOT_TAKE_OWNERSHIP, NumericDiffOptions());
  }  // destructor chạy tại đây
  SUCCEED();
}

// P2: node 1: sai (ownership_ == TAKE_OWNERSHIP) -> END
TEST(NumericDiffFirstOrderFunctionDtorTest, TakeOwnership) {
  QuadraticCostFunctor* functor = new QuadraticCostFunctor();
  {
    NumericDiffFirstOrderFunction<QuadraticCostFunctor, CENTRAL, 4> function(
        functor, TAKE_OWNERSHIP, NumericDiffOptions());
  }  // destructor chạy tại đây, functor_ (unique_ptr) tự giải phóng
  SUCCEED();
}

}  // namespace
}  // namespace ceres
