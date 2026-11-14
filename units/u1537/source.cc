// u1537 – ceres::GradientProblemSolver::Solve
// Trích từ internal/ceres/gradient_problem_solver.cc, dòng 98–201 (chỉ để xem, không compile)

void GradientProblemSolver::Solve(const GradientProblemSolver::Options& options,
                                  const GradientProblem& problem,
                                  double* parameters_ptr,
                                  GradientProblemSolver::Summary* summary) {
  using internal::CallStatistics;
  using internal::GradientProblemEvaluator;
  using internal::GradientProblemSolverStateUpdatingCallback;
  using internal::LoggingCallback;
  using internal::Minimizer;
  using internal::SetSummaryFinalCost;
  using internal::WallTimeInSeconds;

  double start_time = WallTimeInSeconds();

  CHECK(summary != nullptr);
  *summary = Summary();
  // clang-format off
  summary->num_parameters                    = problem.NumParameters();
  summary->num_tangent_parameters            = problem.NumTangentParameters();
  summary->line_search_direction_type        = options.line_search_direction_type;         //  NOLINT
  summary->line_search_interpolation_type    = options.line_search_interpolation_type;     //  NOLINT
  summary->line_search_type                  = options.line_search_type;
  summary->max_lbfgs_rank                    = options.max_lbfgs_rank;
  summary->nonlinear_conjugate_gradient_type = options.nonlinear_conjugate_gradient_type;  //  NOLINT
  // clang-format on

  // Check validity
  if (!options.IsValid(&summary->message)) {
    LOG(ERROR) << "Terminating: " << summary->message;
    return;
  }

  VectorRef parameters(parameters_ptr, problem.NumParameters());
  Vector solution(problem.NumParameters());
  solution = parameters;

  // TODO(sameeragarwal): This is a bit convoluted, we should be able
  // to convert to minimizer options directly, but this will do for
  // now.
  Minimizer::Options minimizer_options =
      Minimizer::Options(GradientProblemSolverOptionsToSolverOptions(options));
  minimizer_options.evaluator =
      std::make_unique<GradientProblemEvaluator>(problem);

  std::unique_ptr<IterationCallback> logging_callback;
  if (options.logging_type != SILENT) {
    logging_callback = std::make_unique<LoggingCallback>(
        LINE_SEARCH, options.minimizer_progress_to_stdout);
    minimizer_options.callbacks.insert(minimizer_options.callbacks.begin(),
                                       logging_callback.get());
  }

  std::unique_ptr<IterationCallback> state_updating_callback;
  if (options.update_state_every_iteration) {
    state_updating_callback =
        std::make_unique<GradientProblemSolverStateUpdatingCallback>(
            problem.NumParameters(), solution.data(), parameters_ptr);
    minimizer_options.callbacks.insert(minimizer_options.callbacks.begin(),
                                       state_updating_callback.get());
  }

  std::unique_ptr<Minimizer> minimizer(Minimizer::Create(LINE_SEARCH));

  Solver::Summary solver_summary;
  solver_summary.fixed_cost = 0.0;
  solver_summary.preprocessor_time_in_seconds = 0.0;
  solver_summary.postprocessor_time_in_seconds = 0.0;
  solver_summary.line_search_polynomial_minimization_time_in_seconds = 0.0;

  minimizer->Minimize(minimizer_options, solution.data(), &solver_summary);

  // clang-format off
  summary->termination_type = solver_summary.termination_type;
  summary->message          = solver_summary.message;
  summary->initial_cost     = solver_summary.initial_cost;
  summary->final_cost       = solver_summary.final_cost;
  summary->iterations       = solver_summary.iterations;
  // clang-format on
  summary->line_search_polynomial_minimization_time_in_seconds =
      solver_summary.line_search_polynomial_minimization_time_in_seconds;

  if (summary->IsSolutionUsable()) {
    parameters = solution;
    SetSummaryFinalCost(summary);
  }

  const std::map<std::string, CallStatistics>& evaluator_statistics =
      minimizer_options.evaluator->Statistics();
  {
    const CallStatistics& call_stats = FindWithDefault(
        evaluator_statistics, "Evaluator::Residual", CallStatistics());
    summary->cost_evaluation_time_in_seconds = call_stats.time;
    summary->num_cost_evaluations = call_stats.calls;
  }

  {
    const CallStatistics& call_stats = FindWithDefault(
        evaluator_statistics, "Evaluator::Jacobian", CallStatistics());
    summary->gradient_evaluation_time_in_seconds = call_stats.time;
    summary->num_gradient_evaluations = call_stats.calls;
  }

  summary->total_time_in_seconds = WallTimeInSeconds() - start_time;
}
