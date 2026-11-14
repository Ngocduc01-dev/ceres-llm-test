// u1520 – ceres::internal::LineSearchPreprocessor::Preprocess
// Trích từ internal/ceres/line_search_preprocessor.cc, dòng 72–102 (chỉ để xem, không compile)

bool LineSearchPreprocessor::Preprocess(const Solver::Options& options,
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
    return true;
  }

  if (!SetupEvaluator(pp)) {
    return false;
  }

  SetupCommonMinimizerOptions(pp);
  return true;
}
