// FILE: u0442_test.cc
#include "gtest/gtest.h"
#include "ceres/cubic_interpolation.h"

namespace ceres {
namespace {

// Kiểu thay thế Jet: chỉ cần thành viên a và v mà Evaluate sử dụng.
struct TestJet {
  double a;
  double v;
};

// P1: START -> 1 -> 2(đúng) -> 3 -> 4 -> 2(đúng) -> 3 -> 4 -> 2(sai) -> END
TEST(BiCubicInterpolatorEvaluateJet, TwoIterationsLoop) {
  const double data[8] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
  Grid2D<double, 2> grid(data, 0, 2, 0, 2);
  BiCubicInterpolator<Grid2D<double, 2>> interpolator(grid);

  TestJet r = {0.5, 1.0};
  TestJet c = {0.5, 2.0};
  TestJet f[2];
  f[0] = {0.0, 0.0};
  f[1] = {0.0, 0.0};

  interpolator.Evaluate(r, c, f);
}

}  // namespace
}  // namespace ceres
