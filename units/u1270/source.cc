// u1270 – ceres::GradientProblemSolver::Summary::FullReport
// Trích từ internal/ceres/gradient_problem_solver.cc, dòng 220–288 (chỉ để xem, không compile)

std::string GradientProblemSolver::Summary::FullReport() const {
  using internal::VersionString;

  // NOTE operator+ is not usable for concatenating a string and a string_view.
  std::string report =
      std::string{"\nSolver Summary (v "}.append(VersionString()) + ")\n\n";

  StringAppendF(&report, "Parameters          % 25d\n", num_parameters);
  if (num_tangent_parameters != num_parameters) {
    StringAppendF(
        &report, "Tangent parameters   % 25d\n", num_tangent_parameters);
  }

  std::string line_search_direction_string;
  if (line_search_direction_type == LBFGS) {
    line_search_direction_string = StringPrintf("LBFGS (%d)", max_lbfgs_rank);
  } else if (line_search_direction_type == NONLINEAR_CONJUGATE_GRADIENT) {
    line_search_direction_string = NonlinearConjugateGradientTypeToString(
        nonlinear_conjugate_gradient_type);
  } else {
    line_search_direction_string =
        LineSearchDirectionTypeToString(line_search_direction_type);
  }

  StringAppendF(&report,
                "Line search direction     %19s\n",
                line_search_direction_string.c_str());

  const std::string line_search_type_string = StringPrintf(
      "%s %s",
      LineSearchInterpolationTypeToString(line_search_interpolation_type),
      LineSearchTypeToString(line_search_type));
  StringAppendF(&report,
                "Line search type          %19s\n",
                line_search_type_string.c_str());
  StringAppendF(&report, "\n");

  StringAppendF(&report, "\nCost:\n");
  StringAppendF(&report, "Initial        % 30e\n", initial_cost);
  if (termination_type != FAILURE && termination_type != USER_FAILURE) {
    StringAppendF(&report, "Final          % 30e\n", final_cost);
    StringAppendF(&report, "Change         % 30e\n", initial_cost - final_cost);
  }

  StringAppendF(&report,
                "\nMinimizer iterations         % 16d\n",
                static_cast<int>(iterations.size()));

  StringAppendF(&report, "\nTime (in seconds):\n");
  StringAppendF(&report,
                "\n  Cost evaluation     %23.6f (%d)\n",
                cost_evaluation_time_in_seconds,
                num_cost_evaluations);
  StringAppendF(&report,
                "  Gradient & cost evaluation %16.6f (%d)\n",
                gradient_evaluation_time_in_seconds,
                num_gradient_evaluations);
  StringAppendF(&report,
                "  Polynomial minimization   %17.6f\n",
                line_search_polynomial_minimization_time_in_seconds);
  StringAppendF(
      &report, "Total               %25.6f\n\n", total_time_in_seconds);

  StringAppendF(&report,
                "Termination:        %25s (%s)\n",
                TerminationTypeToString(termination_type),
                message.c_str());
  return report;
}
