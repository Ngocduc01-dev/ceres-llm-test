// FILE: u0354_test.cc
#include "gtest/gtest.h"
#include "ceres/parallel_invoke.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(BlockUntilFinishedConstructorTest, TC1_P1_SingleStraightPath) {
  ceres::internal::BlockUntilFinished block_until_finished(3);
  SUCCEED();
}
