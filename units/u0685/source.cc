// u0685 – ceres::internal::Minimizer::Options::Init
// Trích từ internal/ceres/minimizer.h, dòng 63–112 (chỉ để xem, không compile)

    void Init(const Solver::Options& options) {
      num_threads = options.num_threads;
      max_num_iterations = options.max_num_iterations;
      max_solver_time_in_seconds = options.max_solver_time_in_seconds;
      max_step_solver_retries = 5;
      gradient_tolerance = options.gradient_tolerance;
      parameter_tolerance = options.parameter_tolerance;
      function_tolerance = options.function_tolerance;
      min_relative_decrease = options.min_relative_decrease;
      eta = options.eta;
      jacobi_scaling = options.jacobi_scaling;
      use_nonmonotonic_steps = options.use_nonmonotonic_steps;
      max_consecutive_nonmonotonic_steps =
          options.max_consecutive_nonmonotonic_steps;
      trust_region_problem_dump_directory =
          options.trust_region_problem_dump_directory;
      trust_region_minimizer_iterations_to_dump =
          options.trust_region_minimizer_iterations_to_dump;
      trust_region_problem_dump_format_type =
          options.trust_region_problem_dump_format_type;
      max_num_consecutive_invalid_steps =
          options.max_num_consecutive_invalid_steps;
      min_trust_region_radius = options.min_trust_region_radius;
      line_search_direction_type = options.line_search_direction_type;
      line_search_type = options.line_search_type;
      nonlinear_conjugate_gradient_type =
          options.nonlinear_conjugate_gradient_type;
      max_lbfgs_rank = options.max_lbfgs_rank;
      use_approximate_eigenvalue_bfgs_scaling =
          options.use_approximate_eigenvalue_bfgs_scaling;
      line_search_interpolation_type = options.line_search_interpolation_type;
      min_line_search_step_size = options.min_line_search_step_size;
      line_search_sufficient_function_decrease =
          options.line_search_sufficient_function_decrease;
      max_line_search_step_contraction =
          options.max_line_search_step_contraction;
      min_line_search_step_contraction =
          options.min_line_search_step_contraction;
      max_num_line_search_step_size_iterations =
          options.max_num_line_search_step_size_iterations;
      max_num_line_search_direction_restarts =
          options.max_num_line_search_direction_restarts;
      line_search_sufficient_curvature_decrease =
          options.line_search_sufficient_curvature_decrease;
      max_line_search_step_expansion = options.max_line_search_step_expansion;
      inner_iteration_tolerance = options.inner_iteration_tolerance;
      is_silent = (options.logging_type == SILENT);
      is_constrained = false;
      callbacks = options.callbacks;
    }
