// u1392 – ceres::Solver::Summary::FullReport
// Trích từ internal/ceres/solver.cc, dòng 852–1134 (chỉ để xem, không compile)

std::string Solver::Summary::FullReport() const {
  using internal::VersionString;

  // NOTE operator+ is not usable for concatenating a string and a string_view.
  std::string report =
      std::string{"\nSolver Summary (v "}.append(VersionString()) + ")\n\n";

  StringAppendF(&report, "%45s    %21s\n", "Original", "Reduced");
  StringAppendF(&report,
                "Parameter blocks    % 25d% 25d\n",
                num_parameter_blocks,
                num_parameter_blocks_reduced);
  StringAppendF(&report,
                "Parameters          % 25d% 25d\n",
                num_parameters,
                num_parameters_reduced);
  if (num_effective_parameters_reduced != num_parameters_reduced) {
    StringAppendF(&report,
                  "Effective parameters% 25d% 25d\n",
                  num_effective_parameters,
                  num_effective_parameters_reduced);
  }
  StringAppendF(&report,
                "Residual blocks     % 25d% 25d\n",
                num_residual_blocks,
                num_residual_blocks_reduced);
  StringAppendF(&report,
                "Residuals           % 25d% 25d\n",
                num_residuals,
                num_residuals_reduced);

  if (minimizer_type == TRUST_REGION) {
    // TRUST_SEARCH HEADER
    StringAppendF(
        &report, "\nMinimizer                 %19s\n", "TRUST_REGION");

    if (linear_solver_type_used == DENSE_NORMAL_CHOLESKY ||
        linear_solver_type_used == DENSE_SCHUR ||
        linear_solver_type_used == DENSE_QR) {
      const char* mixed_precision_suffix =
          (mixed_precision_solves_used ? "(Mixed Precision)" : "");
      StringAppendF(&report,
                    "\nDense linear algebra library  %15s %s\n",
                    DenseLinearAlgebraLibraryTypeToString(
                        dense_linear_algebra_library_type),
                    mixed_precision_suffix);
    }

    StringAppendF(&report,
                  "Trust region strategy     %19s",
                  TrustRegionStrategyTypeToString(trust_region_strategy_type));
    if (trust_region_strategy_type == DOGLEG) {
      if (dogleg_type == TRADITIONAL_DOGLEG) {
        StringAppendF(&report, " (TRADITIONAL)");
      } else {
        StringAppendF(&report, " (SUBSPACE)");
      }
    }

    const bool used_sparse_linear_algebra_library =
        linear_solver_type_used == SPARSE_NORMAL_CHOLESKY ||
        linear_solver_type_used == SPARSE_SCHUR ||
        linear_solver_type_used == CGNR ||
        (linear_solver_type_used == ITERATIVE_SCHUR &&
         (preconditioner_type_used == CLUSTER_JACOBI ||
          preconditioner_type_used == CLUSTER_TRIDIAGONAL));

    const bool linear_solver_ordering_required =
        linear_solver_type_used == SPARSE_SCHUR ||
        (linear_solver_type_used == ITERATIVE_SCHUR &&
         (preconditioner_type_used == CLUSTER_JACOBI ||
          preconditioner_type_used == CLUSTER_TRIDIAGONAL)) ||
        (linear_solver_type_used == CGNR && preconditioner_type_used == SUBSET);

    if (used_sparse_linear_algebra_library) {
      const char* mixed_precision_suffix =
          (mixed_precision_solves_used ? "(Mixed Precision)" : "");
      if (linear_solver_ordering_required) {
        StringAppendF(
            &report,
            "\nSparse linear algebra library %15s + %s %s\n",
            SparseLinearAlgebraLibraryTypeToString(
                sparse_linear_algebra_library_type),
            LinearSolverOrderingTypeToString(linear_solver_ordering_type),
            mixed_precision_suffix);
      } else {
        StringAppendF(&report,
                      "\nSparse linear algebra library %15s %s\n",
                      SparseLinearAlgebraLibraryTypeToString(
                          sparse_linear_algebra_library_type),
                      mixed_precision_suffix);
      }
    }

    StringAppendF(&report, "\n");
    StringAppendF(&report, "%45s    %21s\n", "Given", "Used");
    StringAppendF(&report,
                  "Linear solver       %25s%25s\n",
                  LinearSolverTypeToString(linear_solver_type_given),
                  LinearSolverTypeToString(linear_solver_type_used));

    if (IsIterativeSolver(linear_solver_type_given)) {
      StringAppendF(&report,
                    "Preconditioner      %25s%25s\n",
                    PreconditionerTypeToString(preconditioner_type_given),
                    PreconditionerTypeToString(preconditioner_type_used));
    }

    if (preconditioner_type_used == CLUSTER_JACOBI ||
        preconditioner_type_used == CLUSTER_TRIDIAGONAL) {
      StringAppendF(
          &report,
          "Visibility clustering%24s%25s\n",
          VisibilityClusteringTypeToString(visibility_clustering_type),
          VisibilityClusteringTypeToString(visibility_clustering_type));
    }
    StringAppendF(&report,
                  "Threads             % 25d% 25d\n",
                  num_threads_given,
                  num_threads_used);

    std::string given;
    StringifyOrdering(linear_solver_ordering_given, &given);
    std::string used;
    StringifyOrdering(linear_solver_ordering_used, &used);
    StringAppendF(&report,
                  "Linear solver ordering %22s %24s\n",
                  given.c_str(),
                  used.c_str());
    if (IsSchurType(linear_solver_type_used)) {
      StringAppendF(&report,
                    "Schur structure        %22s %24s\n",
                    schur_structure_given.c_str(),
                    schur_structure_used.c_str());
    }

    if (inner_iterations_given) {
      StringAppendF(&report,
                    "Use inner iterations     %20s     %20s\n",
                    inner_iterations_given ? "True" : "False",
                    inner_iterations_used ? "True" : "False");
    }

    if (inner_iterations_used) {
      std::string given;
      StringifyOrdering(inner_iteration_ordering_given, &given);
      std::string used;
      StringifyOrdering(inner_iteration_ordering_used, &used);
      StringAppendF(&report,
                    "Inner iteration ordering %20s %24s\n",
                    given.c_str(),
                    used.c_str());
    }
  } else {
    // LINE_SEARCH HEADER
    StringAppendF(&report, "\nMinimizer                 %19s\n", "LINE_SEARCH");

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

    StringAppendF(&report, "%45s    %21s\n", "Given", "Used");
    StringAppendF(&report,
                  "Threads             % 25d% 25d\n",
                  num_threads_given,
                  num_threads_used);
  }

  StringAppendF(&report, "\nCost:\n");
  StringAppendF(&report, "Initial        % 30e\n", initial_cost);
  if (termination_type != FAILURE && termination_type != USER_FAILURE) {
    StringAppendF(&report, "Final          % 30e\n", final_cost);
    StringAppendF(&report, "Change         % 30e\n", initial_cost - final_cost);
  }

  StringAppendF(&report,
                "\nMinimizer iterations         % 16d\n",
                num_successful_steps + num_unsuccessful_steps);

  // Successful/Unsuccessful steps only matter in the case of the
  // trust region solver. Line search terminates when it encounters
  // the first unsuccessful step.
  if (minimizer_type == TRUST_REGION) {
    StringAppendF(&report,
                  "Successful steps               % 14d\n",
                  num_successful_steps);
    StringAppendF(&report,
                  "Unsuccessful steps             % 14d\n",
                  num_unsuccessful_steps);
  }
  if (inner_iterations_used) {
    StringAppendF(&report,
                  "Steps with inner iterations    % 14d\n",
                  num_inner_iteration_steps);
  }

  const bool line_search_used =
      (minimizer_type == LINE_SEARCH ||
       (minimizer_type == TRUST_REGION && is_constrained));

  if (line_search_used) {
    StringAppendF(&report,
                  "Line search steps              % 14d\n",
                  num_line_search_steps);
  }

  StringAppendF(&report, "\nTime (in seconds):\n");
  StringAppendF(
      &report, "Preprocessor        %25.6f\n", preprocessor_time_in_seconds);

  StringAppendF(&report,
                "\n  Residual only evaluation %18.6f (%d)\n",
                residual_evaluation_time_in_seconds,
                num_residual_evaluations);
  if (line_search_used) {
    StringAppendF(&report,
                  "    Line search cost evaluation    %10.6f\n",
                  line_search_cost_evaluation_time_in_seconds);
  }
  StringAppendF(&report,
                "  Jacobian & residual evaluation %12.6f (%d)\n",
                jacobian_evaluation_time_in_seconds,
                num_jacobian_evaluations);
  if (line_search_used) {
    StringAppendF(&report,
                  "    Line search gradient evaluation   %6.6f\n",
                  line_search_gradient_evaluation_time_in_seconds);
  }

  if (minimizer_type == TRUST_REGION) {
    StringAppendF(&report,
                  "  Linear solver       %23.6f (%d)\n",
                  linear_solver_time_in_seconds,
                  num_linear_solves);
  }

  if (inner_iterations_used) {
    StringAppendF(&report,
                  "  Inner iterations    %23.6f\n",
                  inner_iteration_time_in_seconds);
  }

  if (line_search_used) {
    StringAppendF(&report,
                  "  Line search polynomial minimization  %.6f\n",
                  line_search_polynomial_minimization_time_in_seconds);
  }

  StringAppendF(
      &report, "Minimizer           %25.6f\n\n", minimizer_time_in_seconds);

  StringAppendF(
      &report, "Postprocessor        %24.6f\n", postprocessor_time_in_seconds);

  StringAppendF(
      &report, "Total               %25.6f\n\n", total_time_in_seconds);

  StringAppendF(&report,
                "Termination:        %25s (%s)\n",
                TerminationTypeToString(termination_type),
                message.c_str());
  return report;
}
