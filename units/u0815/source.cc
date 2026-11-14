// u0815 – ceres::(anonymous)::CommonOptionsAreValid
// Trích từ internal/ceres/solver.cc, dòng 97–109 (chỉ để xem, không compile)

bool CommonOptionsAreValid(const Solver::Options& options, std::string* error) {
  OPTION_GE(max_num_iterations, 0);
  OPTION_GE(max_solver_time_in_seconds, 0.0);
  OPTION_GE(function_tolerance, 0.0);
  OPTION_GE(gradient_tolerance, 0.0);
  OPTION_GE(parameter_tolerance, 0.0);
  OPTION_GT(num_threads, 0);
  if (options.check_gradients) {
    OPTION_GT(gradient_check_relative_precision, 0.0);
    OPTION_GT(gradient_check_numeric_derivative_relative_step_size, 0.0);
  }
  return true;
}
