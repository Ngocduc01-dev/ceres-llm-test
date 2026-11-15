// FILE: u1267_test.cc
#include "gtest/gtest.h"
#include "ceres/eigen_vector_ops.h"
#include "ceres/implicit_schur_complement.h"
#include "ceres/parallel_vector_ops.h"
#include "ceres/power_series_expansion_preconditioner.h"

// P1: START -> 1 -> END
TEST(u1267_Test, TC1_CallsTarget) {
  ceres::internal::PowerSeriesExpansionPreconditioner target{};
  target.RightMultiplyAndAccumulate(nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1267_Test, TC2_CallsTarget) {
  ceres::internal::PowerSeriesExpansionPreconditioner target{};
  target.RightMultiplyAndAccumulate(nullptr, nullptr);
}
