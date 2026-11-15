// FILE: u0652_test.cc
#include "gtest/gtest.h"
#include "ceres/callbacks.h"
#include "ceres/program.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0652, CallsTarget) {
  double program_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double parameters_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.StateUpdatingCallback(program_data, parameters_data);
}
