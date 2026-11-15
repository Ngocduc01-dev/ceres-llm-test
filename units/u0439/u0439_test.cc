// FILE: u0439_test.cc
#include "gtest/gtest.h"
#include "ceres/cubic_interpolation.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0439, PathP1) {
  const JetT& arg_0{}
  const JetT& arg_0{};
  JetT* arg_1 = nullptr;
  ceres::CubicInterpolator<Grid1D<double, 2>>::Evaluate<Jet<double, 4>> target(arg_0, arg_1);
  target.Evaluate(arg_0, nullptr);
}
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0439, PathP2) {
  const JetT& arg_0{}
  const JetT& arg_0{};
  JetT* arg_1 = nullptr;
  ceres::CubicInterpolator<Grid1D<double, 2>>::Evaluate<Jet<double, 4>> target(arg_0, arg_1);
  target.Evaluate(arg_0, nullptr);
}
