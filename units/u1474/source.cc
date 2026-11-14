// u1474 – ceres::internal::ProgramEvaluator::CreateEvaluatorScratch
// Trích từ internal/ceres/program_evaluator.h, dòng 361–379 (chỉ để xem, không compile)

  static std::unique_ptr<EvaluateScratch[]> CreateEvaluatorScratch(
      const Program& program, unsigned num_threads) {
    int max_parameters_per_residual_block =
        program.MaxParametersPerResidualBlock();
    int max_scratch_doubles_needed_for_evaluate =
        program.MaxScratchDoublesNeededForEvaluate();
    int max_residuals_per_residual_block =
        program.MaxResidualsPerResidualBlock();
    int num_parameters = program.NumEffectiveParameters();

    auto evaluate_scratch = std::make_unique<EvaluateScratch[]>(num_threads);
    for (int i = 0; i < num_threads; i++) {
      evaluate_scratch[i].Init(max_parameters_per_residual_block,
                               max_scratch_doubles_needed_for_evaluate,
                               max_residuals_per_residual_block,
                               num_parameters);
    }
    return evaluate_scratch;
  }
