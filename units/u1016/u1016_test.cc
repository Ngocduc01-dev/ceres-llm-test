// FILE: u1016_test.cc
#include "gtest/gtest.h"
#include "ceres/implicit_schur_complement.h"
#include "ceres/power_series_expansion_preconditioner.h"

// P1: START -> 1 -> END
TEST(num_rowsTest, TC1_CallsTarget) {
  PowerSeriesExpansionPreconditioner object{};
  object.num_rows();
}

