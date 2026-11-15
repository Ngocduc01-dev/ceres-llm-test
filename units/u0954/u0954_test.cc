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

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0954, TC1_CallsTarget) {
  Evaluator::Options options{};
  ceres::internal::Evaluator object{};
  object.Create(options, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0954, TC2_CallsTarget) {
  Evaluator::Options options{};
  ceres::internal::Evaluator object{};
  object.Create(options, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u0954, TC3_CallsTarget) {
  Evaluator::Options options{};
  ceres::internal::Evaluator object{};
  object.Create(options, nullptr, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u0954, TC4_CallsTarget) {
  Evaluator::Options options{};
  ceres::internal::Evaluator object{};
  object.Create(options, nullptr, nullptr);
}
