// FILE: u0400_test.cc
#include "gtest/gtest.h"

#define private public
#include "ceres/program_evaluator.h"
#include "ceres/scratch_evaluate_preparer.h"
#include "ceres/dense_jacobian_writer.h"
#undef private

namespace ceres {
namespace internal {

using TestProgramEvaluator =
    ProgramEvaluator<ScratchEvaluatePreparer, DenseJacobianWriter>;
using EvaluateScratch = TestProgramEvaluator::EvaluateScratch;

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(EvaluateScratchInitTest, TC1_P1_SequentialPath) {
  EvaluateScratch obj;
  obj.Init(/*max_parameters_per_residual_block=*/3,
           /*max_scratch_doubles_needed_for_evaluate=*/4,
           /*max_residuals_per_residual_block=*/2,
           /*num_parameters=*/5);
}

}  // namespace internal
}  // namespace ceres
