// FILE: u1267_test.cc
#include "gtest/gtest.h"
#include "ceres/eigen_vector_ops.h"
#include "ceres/implicit_schur_complement.h"
#include "ceres/parallel_vector_ops.h"
#include "ceres/power_series_expansion_preconditioner.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1267, TC1_CallsTarget) {
  ceres::internal::PowerSeriesExpansionPreconditioner object{};
  object.RightMultiplyAndAccumulate(nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1267, TC2_CallsTarget) {
  ceres::internal::PowerSeriesExpansionPreconditioner object{};
  object.RightMultiplyAndAccumulate(nullptr, nullptr);
}
