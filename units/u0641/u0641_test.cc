// FILE: u0641_test.cc
#include "gtest/gtest.h"
#include "ceres/numeric_diff_first_order_function.h"
#include "ceres/numeric_diff_options.h"

// Path P1 calls NumericDiffFirstOrderFunction(FirstOrderFunctor * functor, Ownership ownership, const NumericDiffOptions & options).
TEST(Unitu0641, CallsTarget) {
  double functor_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.NumericDiffFirstOrderFunction(functor_data, {}, {});
}
