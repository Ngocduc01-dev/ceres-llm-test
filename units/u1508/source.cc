// u1508 – ceres::(anonymous)::TrustRegionOptionsAreValid
// Trích từ internal/ceres/solver.cc, dòng 389–436 (chỉ để xem, không compile)

bool TrustRegionOptionsAreValid(const Solver::Options& options,
                                std::string* error) {
  OPTION_GT(initial_trust_region_radius, 0.0);
  OPTION_GT(min_trust_region_radius, 0.0);
  OPTION_GT(max_trust_region_radius, 0.0);
  OPTION_LE_OPTION(min_trust_region_radius, max_trust_region_radius);
  OPTION_LE_OPTION(min_trust_region_radius, initial_trust_region_radius);
  OPTION_LE_OPTION(initial_trust_region_radius, max_trust_region_radius);
  OPTION_GE(min_relative_decrease, 0.0);
  OPTION_GE(min_lm_diagonal, 0.0);
  OPTION_GE(max_lm_diagonal, 0.0);
  OPTION_LE_OPTION(min_lm_diagonal, max_lm_diagonal);
  OPTION_GE(max_num_consecutive_invalid_steps, 0);
  OPTION_GT(eta, 0.0);
  OPTION_GE(min_linear_solver_iterations, 0);
  OPTION_GE(max_linear_solver_iterations, 0);
  OPTION_LE_OPTION(min_linear_solver_iterations, max_linear_solver_iterations);

  if (options.use_inner_iterations) {
    OPTION_GE(inner_iteration_tolerance, 0.0);
  }

  if (options.use_nonmonotonic_steps) {
    OPTION_GT(max_consecutive_nonmonotonic_steps, 0);
  }

  if ((options.trust_region_strategy_type == DOGLEG) &&
      IsIterativeSolver(options.linear_solver_type)) {
    *error =
        "DOGLEG only supports exact factorization based linear "
        "solvers. If you want to use an iterative solver please "
        "use LEVENBERG_MARQUARDT as the trust_region_strategy_type";
    return false;
  }

  if (!OptionsAreValidForLinearSolver(options, error)) {
    return false;
  }

  if (!options.trust_region_minimizer_iterations_to_dump.empty() &&
      options.trust_region_problem_dump_format_type != CONSOLE &&
      options.trust_region_problem_dump_directory.empty()) {
    *error = "Solver::Options::trust_region_problem_dump_directory is empty.";
    return false;
  }

  return true;
}
