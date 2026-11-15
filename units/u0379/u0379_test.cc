// FILE: u0379_test.cc
#include "gtest/gtest.h"
#include "ceres/power_series_expansion_preconditioner.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0379, PathP1) {
  { ceres::internal::PowerSeriesExpansionPreconditioner target; }
}
