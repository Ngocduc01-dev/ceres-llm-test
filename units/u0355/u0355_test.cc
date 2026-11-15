// FILE: u0355_test.cc
#include "gtest/gtest.h"
#include "ceres/parallel_invoke.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(BlockUntilFinishedBlock, TC1_NoJobsReturnsImmediately) {
  ceres::internal::BlockUntilFinished block_until_finished(0);
  block_until_finished.Block();
}
