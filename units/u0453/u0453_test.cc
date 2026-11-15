// FILE: u0453_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"

namespace ceres {

// Path P1: START -> 1 -> 2 -> END (node 1: đúng)
TEST(LossFunctionWrapperDestructorTest, DoNotTakeOwnership) {
  TrivialLoss loss;
  {
    LossFunctionWrapper wrapper(&loss, DO_NOT_TAKE_OWNERSHIP);
  }  // destructor được gọi tại đây
}

// Path P2: START -> 1 -> END (node 1: sai)
TEST(LossFunctionWrapperDestructorTest, TakeOwnership) {
  {
    LossFunctionWrapper wrapper(new TrivialLoss(), TAKE_OWNERSHIP);
  }  // destructor được gọi tại đây, rho_ tự giải phóng
}

}  // namespace ceres
