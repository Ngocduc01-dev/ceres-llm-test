// u1521 – ceres::internal::TrustRegionPreprocessor::Preprocess
// Trích từ internal/ceres/trust_region_preprocessor.cc, dòng 374–406 (chỉ để xem, không compile)

bool TrustRegionPreprocessor::Preprocess(const Solver::Options& options,
                                         ProblemImpl* problem,
                                         PreprocessedProblem* pp) {
  CHECK(pp != nullptr);
  pp->options = options;
  ChangeNumThreadsIfNeeded(&pp->options);

  pp->problem = problem;
  Program* program = problem->mutable_program();
  if (!IsProgramValid(*program, &pp->error)) {
    return false;
  }

  pp->reduced_program = program->CreateReducedProgram(
      &pp->removed_parameter_blocks, &pp->fixed_cost, &pp->error);

  if (pp->reduced_program.get() == nullptr) {
    return false;
  }

  if (pp->reduced_program->NumParameterBlocks() == 0) {
    // The reduced problem has no parameter or residual blocks. There
    // is nothing more to do.
    return true;
  }

  if (!SetupLinearSolver(pp) || !SetupEvaluator(pp) ||
      !SetupInnerIterationMinimizer(pp)) {
    return false;
  }

  return SetupMinimizerOptions(pp);
}
