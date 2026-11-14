// u1358 – ceres::internal::SetupCommonMinimizerOptions
// Trích từ internal/ceres/preprocessor.cc, dòng 75–106 (chỉ để xem, không compile)

void SetupCommonMinimizerOptions(PreprocessedProblem* pp) {
  const Solver::Options& options = pp->options;
  Program* program = pp->reduced_program.get();

  // Assuming that the parameter blocks in the program have been
  // reordered as needed, extract them into a contiguous vector.
  pp->reduced_parameters.resize(program->NumParameters());
  double* reduced_parameters = pp->reduced_parameters.data();
  program->ParameterBlocksToStateVector(reduced_parameters);

  auto context = pp->problem->context();
  Minimizer::Options& minimizer_options = pp->minimizer_options;
  minimizer_options = Minimizer::Options(options);
  minimizer_options.evaluator = pp->evaluator;
  minimizer_options.context = context;

  if (options.logging_type != SILENT) {
    pp->logging_callback = std::make_unique<LoggingCallback>(
        options.minimizer_type, options.minimizer_progress_to_stdout);
    minimizer_options.callbacks.insert(minimizer_options.callbacks.begin(),
                                       pp->logging_callback.get());
  }

  if (options.update_state_every_iteration) {
    pp->state_updating_callback =
        std::make_unique<StateUpdatingCallback>(program, reduced_parameters);
    // This must get pushed to the front of the callbacks so that it
    // is run before any of the user callbacks.
    minimizer_options.callbacks.insert(minimizer_options.callbacks.begin(),
                                       pp->state_updating_callback.get());
  }
}
