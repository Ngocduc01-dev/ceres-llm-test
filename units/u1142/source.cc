// u1142 – ceres::(anonymous)::LineSearchOptionsAreValid
// Trích từ internal/ceres/solver.cc, dòng 438–485 (chỉ để xem, không compile)

bool LineSearchOptionsAreValid(const Solver::Options& options,
                               std::string* error) {
  OPTION_GT(max_lbfgs_rank, 0);
  OPTION_GT(min_line_search_step_size, 0.0);
  OPTION_GT(max_line_search_step_contraction, 0.0);
  OPTION_LT(max_line_search_step_contraction, 1.0);
  OPTION_LT_OPTION(max_line_search_step_contraction,
                   min_line_search_step_contraction);
  OPTION_LE(min_line_search_step_contraction, 1.0);
  OPTION_GE(max_num_line_search_step_size_iterations,
            (options.minimizer_type == ceres::TRUST_REGION ? 0 : 1));
  OPTION_GT(line_search_sufficient_function_decrease, 0.0);
  OPTION_LT_OPTION(line_search_sufficient_function_decrease,
                   line_search_sufficient_curvature_decrease);
  OPTION_LT(line_search_sufficient_curvature_decrease, 1.0);
  OPTION_GT(max_line_search_step_expansion, 1.0);

  if ((options.line_search_direction_type == ceres::BFGS ||
       options.line_search_direction_type == ceres::LBFGS) &&
      options.line_search_type != ceres::WOLFE) {
    *error =
        std::string(
            "Invalid configuration: Solver::Options::line_search_type = ") +
        std::string(LineSearchTypeToString(options.line_search_type)) +
        std::string(
            ". When using (L)BFGS, "
            "Solver::Options::line_search_type must be set to WOLFE.");
    return false;
  }

  // Warn user if they have requested BISECTION interpolation, but constraints
  // on max/min step size change during line search prevent bisection scaling
  // from occurring. Warn only, as this is likely a user mistake, but one
  // which does not prevent us from continuing.
  if (options.line_search_interpolation_type == ceres::BISECTION &&
      (options.max_line_search_step_contraction > 0.5 ||
       options.min_line_search_step_contraction < 0.5)) {
    LOG(WARNING)
        << "Line search interpolation type is BISECTION, but specified "
        << "max_line_search_step_contraction: "
        << options.max_line_search_step_contraction << ", and "
        << "min_line_search_step_contraction: "
        << options.min_line_search_step_contraction
        << ", prevent bisection (0.5) scaling, continuing with solve "
           "regardless.";
  }
  return true;
}
