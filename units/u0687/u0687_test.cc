// FILE: u0687_test.cc
#include "gtest/gtest.h"
#include "ceres/implicit_schur_complement.h"
#include "ceres/power_series_expansion_preconditioner.h"
#include "ceres/preconditioner.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0687, CallsTarget) {
  double isc_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.PowerSeriesExpansionPreconditioner(isc_data, 1, 1.0, {});
}
