// FILE: u0561_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function_to_functor.h"

// Path P1 calls GetParameterPointers(const Tuple& paramPointers, std::integer_sequence<int, Indices>).
TEST(Unitu0561, CallsTarget) {
  object.GetParameterPointers(1, 1);
}
