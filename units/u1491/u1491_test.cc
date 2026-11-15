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

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1491, TC1_CallsTarget) {
  Problem::EvaluateOptions evaluate_options{};
  ceres::internal::ProblemImpl object{};
  object.Evaluate(evaluate_options, nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1491, TC2_CallsTarget) {
  Problem::EvaluateOptions evaluate_options{};
  ceres::internal::ProblemImpl object{};
  object.Evaluate(evaluate_options, nullptr, nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1491, TC3_CallsTarget) {
  Problem::EvaluateOptions evaluate_options{};
  ceres::internal::ProblemImpl object{};
  object.Evaluate(evaluate_options, nullptr, nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1491, TC4_CallsTarget) {
  Problem::EvaluateOptions evaluate_options{};
  ceres::internal::ProblemImpl object{};
  object.Evaluate(evaluate_options, nullptr, nullptr, nullptr, nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1491, TC5_CallsTarget) {
  Problem::EvaluateOptions evaluate_options{};
  ceres::internal::ProblemImpl object{};
  object.Evaluate(evaluate_options, nullptr, nullptr, nullptr, nullptr);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1491, TC6_CallsTarget) {
  Problem::EvaluateOptions evaluate_options{};
  ceres::internal::ProblemImpl object{};
  object.Evaluate(evaluate_options, nullptr, nullptr, nullptr, nullptr);
}

// P7: START -> 1 -> END; branch decisions covered by case 7
TEST(Unit_u1491, TC7_CallsTarget) {
  Problem::EvaluateOptions evaluate_options{};
  ceres::internal::ProblemImpl object{};
  object.Evaluate(evaluate_options, nullptr, nullptr, nullptr, nullptr);
}

// P8: START -> 1 -> END; branch decisions covered by case 8
TEST(Unit_u1491, TC8_CallsTarget) {
  Problem::EvaluateOptions evaluate_options{};
  ceres::internal::ProblemImpl object{};
  object.Evaluate(evaluate_options, nullptr, nullptr, nullptr, nullptr);
}

// P9: START -> 1 -> END; branch decisions covered by case 9
TEST(Unit_u1491, TC9_CallsTarget) {
  Problem::EvaluateOptions evaluate_options{};
  ceres::internal::ProblemImpl object{};
  object.Evaluate(evaluate_options, nullptr, nullptr, nullptr, nullptr);
}

// P10: START -> 1 -> END; branch decisions covered by case 10
TEST(Unit_u1491, TC10_CallsTarget) {
  Problem::EvaluateOptions evaluate_options{};
  ceres::internal::ProblemImpl object{};
  object.Evaluate(evaluate_options, nullptr, nullptr, nullptr, nullptr);
}

// P11: START -> 1 -> END; branch decisions covered by case 11
TEST(Unit_u1491, TC11_CallsTarget) {
  Problem::EvaluateOptions evaluate_options{};
  ceres::internal::ProblemImpl object{};
  object.Evaluate(evaluate_options, nullptr, nullptr, nullptr, nullptr);
}

// P12: START -> 1 -> END; branch decisions covered by case 12
TEST(Unit_u1491, TC12_CallsTarget) {
  Problem::EvaluateOptions evaluate_options{};
  ceres::internal::ProblemImpl object{};
  object.Evaluate(evaluate_options, nullptr, nullptr, nullptr, nullptr);
}

// P13: START -> 1 -> END; branch decisions covered by case 13
TEST(Unit_u1491, TC13_CallsTarget) {
  Problem::EvaluateOptions evaluate_options{};
  ceres::internal::ProblemImpl object{};
  object.Evaluate(evaluate_options, nullptr, nullptr, nullptr, nullptr);
}

// P14: START -> 1 -> END; branch decisions covered by case 14
TEST(Unit_u1491, TC14_CallsTarget) {
  Problem::EvaluateOptions evaluate_options{};
  ceres::internal::ProblemImpl object{};
  object.Evaluate(evaluate_options, nullptr, nullptr, nullptr, nullptr);
}

// P15: START -> 1 -> END; branch decisions covered by case 15
TEST(Unit_u1491, TC15_CallsTarget) {
  Problem::EvaluateOptions evaluate_options{};
  ceres::internal::ProblemImpl object{};
  object.Evaluate(evaluate_options, nullptr, nullptr, nullptr, nullptr);
}

// P16: START -> 1 -> END; branch decisions covered by case 16
TEST(Unit_u1491, TC16_CallsTarget) {
  Problem::EvaluateOptions evaluate_options{};
  ceres::internal::ProblemImpl object{};
  object.Evaluate(evaluate_options, nullptr, nullptr, nullptr, nullptr);
}
