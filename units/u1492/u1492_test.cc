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

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1492, TC1_CallsTarget) {
  Evaluator::EvaluateOptions evaluate_options{};
  ceres::internal::ProgramEvaluator object{};
  object.Evaluate(evaluate_options, nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1492, TC2_CallsTarget) {
  Evaluator::EvaluateOptions evaluate_options{};
  ceres::internal::ProgramEvaluator object{};
  object.Evaluate(evaluate_options, nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1492, TC3_CallsTarget) {
  Evaluator::EvaluateOptions evaluate_options{};
  ceres::internal::ProgramEvaluator object{};
  object.Evaluate(evaluate_options, nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1492, TC4_CallsTarget) {
  Evaluator::EvaluateOptions evaluate_options{};
  ceres::internal::ProgramEvaluator object{};
  object.Evaluate(evaluate_options, nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1492, TC5_CallsTarget) {
  Evaluator::EvaluateOptions evaluate_options{};
  ceres::internal::ProgramEvaluator object{};
  object.Evaluate(evaluate_options, nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1492, TC6_CallsTarget) {
  Evaluator::EvaluateOptions evaluate_options{};
  ceres::internal::ProgramEvaluator object{};
  object.Evaluate(evaluate_options, nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P7: START -> 1 -> END; branch decisions covered by case 7
TEST(Unit_u1492, TC7_CallsTarget) {
  Evaluator::EvaluateOptions evaluate_options{};
  ceres::internal::ProgramEvaluator object{};
  object.Evaluate(evaluate_options, nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P8: START -> 1 -> END; branch decisions covered by case 8
TEST(Unit_u1492, TC8_CallsTarget) {
  Evaluator::EvaluateOptions evaluate_options{};
  ceres::internal::ProgramEvaluator object{};
  object.Evaluate(evaluate_options, nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P9: START -> 1 -> END; branch decisions covered by case 9
TEST(Unit_u1492, TC9_CallsTarget) {
  Evaluator::EvaluateOptions evaluate_options{};
  ceres::internal::ProgramEvaluator object{};
  object.Evaluate(evaluate_options, nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P10: START -> 1 -> END; branch decisions covered by case 10
TEST(Unit_u1492, TC10_CallsTarget) {
  Evaluator::EvaluateOptions evaluate_options{};
  ceres::internal::ProgramEvaluator object{};
  object.Evaluate(evaluate_options, nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P11: START -> 1 -> END; branch decisions covered by case 11
TEST(Unit_u1492, TC11_CallsTarget) {
  Evaluator::EvaluateOptions evaluate_options{};
  ceres::internal::ProgramEvaluator object{};
  object.Evaluate(evaluate_options, nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P12: START -> 1 -> END; branch decisions covered by case 12
TEST(Unit_u1492, TC12_CallsTarget) {
  Evaluator::EvaluateOptions evaluate_options{};
  ceres::internal::ProgramEvaluator object{};
  object.Evaluate(evaluate_options, nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P13: START -> 1 -> END; branch decisions covered by case 13
TEST(Unit_u1492, TC13_CallsTarget) {
  Evaluator::EvaluateOptions evaluate_options{};
  ceres::internal::ProgramEvaluator object{};
  object.Evaluate(evaluate_options, nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P14: START -> 1 -> END; branch decisions covered by case 14
TEST(Unit_u1492, TC14_CallsTarget) {
  Evaluator::EvaluateOptions evaluate_options{};
  ceres::internal::ProgramEvaluator object{};
  object.Evaluate(evaluate_options, nullptr, nullptr, nullptr, nullptr, nullptr);
}
