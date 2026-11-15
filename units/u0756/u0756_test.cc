// FILE: u0756_test.cc
#include "gtest/gtest.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0756, TC1_CallsTarget) {
  NonlinearConjugateGradientType type{};
  ceres::NonlinearConjugateGradientTypeToString(type);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0756, TC2_CallsTarget) {
  NonlinearConjugateGradientType type{};
  ceres::NonlinearConjugateGradientTypeToString(type);
}
