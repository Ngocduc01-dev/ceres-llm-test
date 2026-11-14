// u1507 – ceres::internal::ArmijoLineSearch::DoSearch
// Trích từ internal/ceres/line_search.cc, dòng 280–365 (chỉ để xem, không compile)

void ArmijoLineSearch::DoSearch(const double step_size_estimate,
                                const double initial_cost,
                                const double initial_gradient,
                                Summary* summary) const {
  CHECK_GE(step_size_estimate, 0.0);
  CHECK_GT(options().sufficient_decrease, 0.0);
  CHECK_LT(options().sufficient_decrease, 1.0);
  CHECK_GT(options().max_num_iterations, 0);
  LineSearchFunction* function = options().function;

  // Note initial_cost & initial_gradient are evaluated at step_size = 0,
  // not step_size_estimate, which is our starting guess.
  FunctionSample initial_position(0.0, initial_cost, initial_gradient);
  initial_position.vector_x = function->position();
  initial_position.vector_x_is_valid = true;

  const double descent_direction_max_norm = function->DirectionInfinityNorm();
  FunctionSample previous;
  FunctionSample current;

  // As the Armijo line search algorithm always uses the initial point, for
  // which both the function value and derivative are known, when fitting a
  // minimizing polynomial, we can fit up to a quadratic without requiring the
  // gradient at the current query point.
  const bool kEvaluateGradient = options().interpolation_type == CUBIC;

  ++summary->num_function_evaluations;
  if (kEvaluateGradient) {
    ++summary->num_gradient_evaluations;
  }

  function->Evaluate(step_size_estimate, kEvaluateGradient, &current);
  while (!current.value_is_valid ||
         current.value > (initial_cost + options().sufficient_decrease *
                                             initial_gradient * current.x)) {
    // If current.value_is_valid is false, we treat it as if the cost at that
    // point is not large enough to satisfy the sufficient decrease condition.
    ++summary->num_iterations;
    if (summary->num_iterations >= options().max_num_iterations) {
      summary->error = StringPrintf(
          "Line search failed: Armijo failed to find a point "
          "satisfying the sufficient decrease condition within "
          "specified max_num_iterations: %d.",
          options().max_num_iterations);
      if (!options().is_silent) {
        LOG(WARNING) << summary->error;
      }
      return;
    }

    const double polynomial_minimization_start_time = WallTimeInSeconds();
    const double step_size = this->InterpolatingPolynomialMinimizingStepSize(
        options().interpolation_type,
        initial_position,
        previous,
        current,
        (options().max_step_contraction * current.x),
        (options().min_step_contraction * current.x));
    summary->polynomial_minimization_time_in_seconds +=
        (WallTimeInSeconds() - polynomial_minimization_start_time);

    if (step_size * descent_direction_max_norm < options().min_step_size) {
      summary->error = StringPrintf(
          "Line search failed: step_size too small: %.5e "
          "with descent_direction_max_norm: %.5e.",
          step_size,
          descent_direction_max_norm);
      if (!options().is_silent) {
        LOG(WARNING) << summary->error;
      }
      return;
    }

    previous = current;

    ++summary->num_function_evaluations;
    if (kEvaluateGradient) {
      ++summary->num_gradient_evaluations;
    }

    function->Evaluate(step_size, kEvaluateGradient, &current);
  }

  summary->optimal_point = current;
  summary->success = true;
}
