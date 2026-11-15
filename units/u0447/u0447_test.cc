// FILE: u0447_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/autodiff.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0447, PathP1) {
  int arg_0 = 1;
  JetT* arg_1 = nullptr;
  T** arg_2 = nullptr;
  ceres::Take1stOrderParts<integer_sequence<int, 2, 2>>::Apply<Jet<double, 4>, double> target(arg_0, arg_1, arg_2);
  target.Apply(1, nullptr, nullptr);
}

// Path P2: START -> 1 -> END.
TEST(Unit_u0447, PathP2) {
  int arg_0 = 1;
  JetT* arg_1 = nullptr;
  T** arg_2 = nullptr;
  ceres::Take1stOrderParts<integer_sequence<int, 2, 2>>::Apply<Jet<double, 4>, double> target(arg_0, arg_1, arg_2);
  target.Apply(1, nullptr, nullptr);
}
