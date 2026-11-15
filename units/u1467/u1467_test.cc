// FILE: u1467_test.cc
#include "gtest/gtest.h"
#include "ceres/iteration_callback.h"
#include "ceres/callbacks.h"

// P1: START -> 1 -> END
TEST(u1467_Test, TC1_CallsTarget) {
  ceres::internal::StateUpdatingCallback target{};
  target.operator()(nullptr);
}
