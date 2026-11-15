// FILE: u1016_test.cc
#include "gtest/gtest.h"
#include "ceres/implicit_schur_complement.h"
#include "ceres/power_series_expansion_preconditioner.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1016, TC1_CallsTarget) {
  ceres::internal::PowerSeriesExpansionPreconditioner object{};
  object.num_rows();
}
