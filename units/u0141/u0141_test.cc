// FILE: u0141_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(IsUnorderedJetTest, P1_JetJet) {
  const Jet<double, 1> f(1.5);
  const Jet<double, 1> g(-2.25);
  [[maybe_unused]] const bool result = ceres::isunordered(f, g);
}

}  // namespace
}  // namespace ceres
