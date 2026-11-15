// FILE: u0107_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace {

// P1: START -> 1 -> END (hàm không có điểm rẽ nhánh)
TEST(JetCosTest, P1_SinglePath) {
  Jet<double, 7> f;
  f.a = 0.7;
  f.v[0] = -3.2;
  f.v[1] = 1.5;
  f.v[2] = 0.4;
  f.v[3] = 2.8;
  f.v[4] = -0.9;
  f.v[5] = 4.1;
  f.v[6] = -1.7;

  Jet<double, 7> r = cos(f);
  (void)r;
}

}  // namespace
}  // namespace ceres
