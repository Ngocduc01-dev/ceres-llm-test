// FILE: u0442_test.cc
#include "gtest/gtest.h"
#include "ceres/cubic_interpolation.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0442, PathP1) {
  const JetT& arg_0{}
  const JetT& arg_1{}
  const JetT& arg_0{};
  const JetT& arg_1{};
  JetT* arg_2 = nullptr;
  ceres::BiCubicInterpolator<Grid2D<double, 2>>::Evaluate<Jet<double, 4>> target(arg_0, arg_1, arg_2);
  target.Evaluate(arg_0, arg_1, nullptr);
}

// Path P2: START -> 1 -> END.
TEST(Unit_u0442, PathP2) {
  const JetT& arg_0{}
  const JetT& arg_1{}
  const JetT& arg_0{};
  const JetT& arg_1{};
  JetT* arg_2 = nullptr;
  ceres::BiCubicInterpolator<Grid2D<double, 2>>::Evaluate<Jet<double, 4>> target(arg_0, arg_1, arg_2);
  target.Evaluate(arg_0, arg_1, nullptr);
}
