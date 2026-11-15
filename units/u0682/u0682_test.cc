// FILE: u0682_test.cc
#include "gtest/gtest.h"
#include "ceres/line_search_direction.h"

// Path P1 calls NonlinearConjugateGradient(const NonlinearConjugateGradientType type, const double function_tolerance).
TEST(Unitu0682, CallsTarget) {
  object.NonlinearConjugateGradient({}, 1.0);
}
