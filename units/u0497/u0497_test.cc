// FILE: u0497_test.cc
#include <sstream>

#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace {

// P1: node 2: sai (0 lần lặp, N=0)
TEST(JetOutputStreamCFT, TC1_ZeroIterations) {
  Jet<double, 0> z;
  z.a = 3.5;
  std::ostringstream os;
  os << z;
}

// P2: node 2: đúng, sai; node 4: sai (1 lần lặp, N=1)
TEST(JetOutputStreamCFT, TC2_OneIteration) {
  Jet<double, 1> z;
  z.a = -2.25;
  z.v[0] = 7.5;
  std::ostringstream os;
  os << z;
}

// P3: node 2: đúng, sai; node 4: đúng, sai (2 lần lặp, N=2)
TEST(JetOutputStreamCFT, TC3_TwoIterations) {
  Jet<double, 2> z;
  z.a = 1.5;
  z.v[0] = -4.0;
  z.v[1] = 6.25;
  std::ostringstream os;
  os << z;
}

// P4: node 2: đúng, sai; node 4: đúng, sai (3 lần lặp, giá trị ở giữa, N=3)
TEST(JetOutputStreamCFT, TC4_MiddleIterations) {
  Jet<double, 3> z;
  z.a = 8.0;
  z.v[0] = 2.5;
  z.v[1] = -1.5;
  z.v[2] = 9.0;
  std::ostringstream os;
  os << z;
}

// P5: node 2: đúng, sai; node 4: đúng, sai (n-1 = 4 lần lặp, N=4)
TEST(JetOutputStreamCFT, TC5_NMinusOneIterations) {
  Jet<double, 4> z;
  z.a = -6.5;
  z.v[0] = 0.5;
  z.v[1] = 3.0;
  z.v[2] = -7.0;
  z.v[3] = 5.5;
  std::ostringstream os;
  os << z;
}

// P6: node 2: đúng, sai; node 4: đúng, sai (n = 5 lần lặp, N=5)
TEST(JetOutputStreamCFT, TC6_NIterations) {
  Jet<double, 5> z;
  z.a = 4.75;
  z.v[0] = -3.5;
  z.v[1] = 1.0;
  z.v[2] = 6.0;
  z.v[3] = -9.0;
  z.v[4] = 2.0;
  std::ostringstream os;
  os << z;
}

}  // namespace
}  // namespace ceres
