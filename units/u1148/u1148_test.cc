// FILE: u1148_test.cc
#include "gtest/gtest.h"
#include "ceres/context.h"
#include "ceres/context_impl.h"

// P1: START -> 1 -> END
TEST(CreateTest, TC1_CallsTarget) {
  Context object{};
  object.Create();
}

