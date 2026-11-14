// u0790 – ceres::(anonymous)::GradientProblemSolverOptionsToSolverOptions
// Trích từ internal/ceres/gradient_problem_solver.cc, dòng 56–86 (chỉ để xem, không compile)

Solver::Options GradientProblemSolverOptionsToSolverOptions(
    const GradientProblemSolver::Options& options) {
#define COPY_OPTION(x) solver_options.x = options.x

  Solver::Options solver_options;
  solver_options.minimizer_type = LINE_SEARCH;
  COPY_OPTION(line_search_direction_type);
  COPY_OPTION(line_search_type);
  COPY_OPTION(nonlinear_conjugate_gradient_type);
  COPY_OPTION(max_lbfgs_rank);
  COPY_OPTION(use_approximate_eigenvalue_bfgs_scaling);
  COPY_OPTION(line_search_interpolation_type);
  COPY_OPTION(min_line_search_step_size);
  COPY_OPTION(line_search_sufficient_function_decrease);
  COPY_OPTION(max_line_search_step_contraction);
  COPY_OPTION(min_line_search_step_contraction);
  COPY_OPTION(max_num_line_search_step_size_iterations);
  COPY_OPTION(max_num_line_search_direction_restarts);
  COPY_OPTION(line_search_sufficient_curvature_decrease);
  COPY_OPTION(max_line_search_step_expansion);
  COPY_OPTION(max_num_iterations);
  COPY_OPTION(max_solver_time_in_seconds);
  COPY_OPTION(parameter_tolerance);
  COPY_OPTION(function_tolerance);
  COPY_OPTION(gradient_tolerance);
  COPY_OPTION(logging_type);
  COPY_OPTION(minimizer_progress_to_stdout);
  COPY_OPTION(callbacks);
  return solver_options;
#undef COPY_OPTION
}
