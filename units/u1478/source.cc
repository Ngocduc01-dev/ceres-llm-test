// u1478 – ceres::(anonymous)::PostSolveSummarize
// Trích từ internal/ceres/solver.cc, dòng 565–625 (chỉ để xem, không compile)

void PostSolveSummarize(const internal::PreprocessedProblem& pp,
                        Solver::Summary* summary) {
  internal::OrderingToGroupSizes(pp.options.linear_solver_ordering.get(),
                                 &(summary->linear_solver_ordering_used));
  // TODO(sameeragarwal): Update the preprocessor to collapse the
  // second and higher groups into one group when nested dissection is
  // used.
  internal::OrderingToGroupSizes(pp.options.inner_iteration_ordering.get(),
                                 &(summary->inner_iteration_ordering_used));

  // clang-format off
  summary->inner_iterations_used          = pp.inner_iteration_minimizer != nullptr;
  summary->linear_solver_type_used        = pp.linear_solver_options.type;
  summary->mixed_precision_solves_used    = pp.options.use_mixed_precision_solves;
  summary->num_threads_used               = pp.options.num_threads;
  summary->preconditioner_type_used       = pp.options.preconditioner_type;
  // clang-format on

  internal::SetSummaryFinalCost(summary);

  if (pp.reduced_program != nullptr) {
    SummarizeReducedProgram(*pp.reduced_program, summary);
  }

  using internal::CallStatistics;

  // It is possible that no evaluator was created. This would be the
  // case if the preprocessor failed, or if the reduced problem did
  // not contain any parameter blocks. Thus, only extract the
  // evaluator statistics if one exists.
  if (pp.evaluator != nullptr) {
    const std::map<std::string, CallStatistics>& evaluator_statistics =
        pp.evaluator->Statistics();
    {
      const CallStatistics& call_stats = FindWithDefault(
          evaluator_statistics, "Evaluator::Residual", CallStatistics());

      summary->residual_evaluation_time_in_seconds = call_stats.time;
      summary->num_residual_evaluations = call_stats.calls;
    }
    {
      const CallStatistics& call_stats = FindWithDefault(
          evaluator_statistics, "Evaluator::Jacobian", CallStatistics());

      summary->jacobian_evaluation_time_in_seconds = call_stats.time;
      summary->num_jacobian_evaluations = call_stats.calls;
    }
  }

  // Again, like the evaluator, there may or may not be a linear
  // solver from which we can extract run time statistics. In
  // particular the line search solver does not use a linear solver.
  if (pp.linear_solver != nullptr) {
    const std::map<std::string, CallStatistics>& linear_solver_statistics =
        pp.linear_solver->Statistics();
    const CallStatistics& call_stats = FindWithDefault(
        linear_solver_statistics, "LinearSolver::Solve", CallStatistics());
    summary->num_linear_solves = call_stats.calls;
    summary->linear_solver_time_in_seconds = call_stats.time;
  }
}
