// FILE: u0452_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"

// P1: node 1: đúng (DO_NOT_TAKE_OWNERSHIP) -> node 2 -> END
TEST(ScaledLossDestructorTest, DoNotTakeOwnershipReleasesPointer) {
  ceres::TrivialLoss rho;
  ceres::ScaledLoss* loss =
      new ceres::ScaledLoss(&rho, 1.7, ceres::DO_NOT_TAKE_OWNERSHIP);
  delete loss;
}

// P2: node 1: sai (TAKE_OWNERSHIP) -> END
TEST(ScaledLossDestructorTest, TakeOwnershipDeletesLoss) {
  ceres::ScaledLoss* loss =
      new ceres::ScaledLoss(new ceres::TrivialLoss(), 3.2, ceres::TAKE_OWNERSHIP);
  delete loss;
}
