// FILE: u1492_test.cc
#include "gtest/gtest.h"
#include "ceres/evaluation_callback.h"
#include "ceres/evaluator.h"
#include "ceres/execution_summary.h"
#include "ceres/parallel_vector_ops.h"
#include "ceres/parameter_block.h"
#include "ceres/program_evaluator.h"
#include "ceres/residual_block.h"
#include "ceres/sparse_matrix.h"

// P1: START -> 1 -> END
TEST(u1492_Test, TC1_CallsTarget) {
  ProgramEvaluator<ScratchEvaluatePreparer, DenseJacobianWriter> target{};
  target.Evaluate(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1492_Test, TC2_CallsTarget) {
  ProgramEvaluator<ScratchEvaluatePreparer, DenseJacobianWriter> target{};
  target.Evaluate(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1492_Test, TC3_CallsTarget) {
  ProgramEvaluator<ScratchEvaluatePreparer, DenseJacobianWriter> target{};
  target.Evaluate(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1492_Test, TC4_CallsTarget) {
  ProgramEvaluator<ScratchEvaluatePreparer, DenseJacobianWriter> target{};
  target.Evaluate(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
}
