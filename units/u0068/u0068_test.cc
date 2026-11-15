// FILE: u0068_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// Path P1: START -> 1 -> END
TEST(JetDefaultConstructorTest, DefaultConstructDouble4) {
  ceres::Jet<double, 4> jet;
  (void)jet;
}
