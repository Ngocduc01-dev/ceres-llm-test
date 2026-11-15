// FILE: u0954_test.cc
#include "gtest/gtest.h"
#include "ceres/block_evaluate_preparer.h"
#include "ceres/block_jacobian_writer.h"
#include "ceres/compressed_row_jacobian_writer.h"
#include "ceres/dense_jacobian_writer.h"
#include "ceres/dynamic_compressed_row_finalizer.h"
#include "ceres/dynamic_compressed_row_jacobian_writer.h"
#include "ceres/evaluator.h"
#include "ceres/program.h"
#include "ceres/program_evaluator.h"
#include "ceres/scratch_evaluate_preparer.h"

// P1: START -> 1 -> END
TEST(CreateTest, TC1_CallsTarget) {
  Evaluator object{};
  Evaluator::Options & options a0{};
  object.Create(a0, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(CreateTest, TC2_CallsTarget) {
  Evaluator object{};
  Evaluator::Options & options a0{};
  object.Create(a0, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(CreateTest, TC3_CallsTarget) {
  Evaluator object{};
  Evaluator::Options & options a0{};
  object.Create(a0, nullptr, nullptr);
}

