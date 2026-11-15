// FILE: u1491_test.cc
#include "gtest/gtest.h"
#include "ceres/crs_matrix.h"
#include "ceres/problem.h"
#include "ceres/casts.h"
#include "ceres/compressed_row_jacobian_writer.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/evaluator.h"
#include "ceres/map_util.h"
#include "ceres/parameter_block.h"
#include "ceres/problem_impl.h"
#include "ceres/program.h"
#include "ceres/program_evaluator.h"
#include "ceres/scratch_evaluate_preparer.h"

// P1: START -> 1 -> END
TEST(u1491_Test, TC1_CallsTarget) {
  ceres::internal::ProblemImpl target{};
  target.Evaluate(nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1491_Test, TC2_CallsTarget) {
  ceres::internal::ProblemImpl target{};
  target.Evaluate(nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1491_Test, TC3_CallsTarget) {
  ceres::internal::ProblemImpl target{};
  target.Evaluate(nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1491_Test, TC4_CallsTarget) {
  ceres::internal::ProblemImpl target{};
  target.Evaluate(nullptr, nullptr, nullptr, nullptr, nullptr);
}
