// FILE: u0118_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetCbrtTest, TC1_SinglePath) {
  Jet<double, 2> f;
  f.a = 6.0;
  f.v[0] = 2.0;
  f.v[1] = -3.0;

  Jet<double, 2> r = cbrt(f);
  (void)r;
}

}  // namespace
}  // namespace ceres
